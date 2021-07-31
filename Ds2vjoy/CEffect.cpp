#include	"stdafx.h"
#include	"CEffect.h"

//----------------------------------------------------------------------------------------------
//	Transplant
//	Force Feedback Driver for XInput
//----------------------------------------------------------------------------------------------

CEffect::CEffect()
	:m_Type(FFBEType::ET_NONE)
{
	//	status
	m_Status = 0;
	//	View
	m_PlayCount = 0;
	//	Rebirth moment
	m_StartTime = 0;
}

//----------------------------------------------------------------------------------------------
//	Calc
//----------------------------------------------------------------------------------------------

BOOL CEffect::Calc(
	LONG* LeftLevel
	, LONG* RightLevel
	, double	CurrentTime)
{
	if (m_Status == FALSE)
		return FALSE;

	//	Calculate the playback time, start time, end time, and current time of the effect
	ULONG	Duration = max(1, m_report.Duration);
	double	EndTime = DBL_MAX;
	if (m_PlayCount != -1 && Duration != 0xFFFF)
	{
		EndTime = m_StartTime + Duration * m_PlayCount;
	}

	//	Is the effect playing?
	if (CurrentTime <= EndTime)
	{

		//	Calculate the envelope
		LONG	NormalRate;
		LONG	AttackLevel;
		LONG	FadeLevel;
		CalcEnvelope(
			Duration
			, static_cast<ULONG>(CurrentTime - m_StartTime) % Duration
			, &NormalRate
			, &AttackLevel
			, &FadeLevel);

		//	Calculate the force
		LONG	NormalLevel;
		LONG	WorkLeftLevel;
		LONG	WorkRightLevel;
		CalcForce(
			Duration
			, static_cast<ULONG>(CurrentTime - m_StartTime) % Duration
			, NormalRate
			, AttackLevel
			, FadeLevel
			, &NormalLevel);

		//	Adjust the positive and negative of the force
		WorkLeftLevel = (NormalLevel > 0) ? NormalLevel : -NormalLevel;
		WorkRightLevel = (NormalLevel > 0) ? NormalLevel : -NormalLevel;

		//	Adjust the force cap
		WorkLeftLevel = min(0xFF, WorkLeftLevel * 0xFF / 10000);
		WorkRightLevel = min(0xFF, WorkRightLevel * 0xFF / 10000);

		//	Add force
		*LeftLevel = *LeftLevel + WorkLeftLevel;
		*RightLevel = *RightLevel + WorkRightLevel;
		return TRUE;
	}
	m_Status = FALSE;
	return FALSE;
}

//----------------------------------------------------------------------------------------------
//	CalcEnvelope
//----------------------------------------------------------------------------------------------

VOID CEffect::CalcEnvelope(
	ULONG	Duration
	, ULONG	CurrentPos
	, LONG* NormalRate
	, LONG* AttackLevel
	, LONG* FadeLevel)
{
	//	Calculate the envelope
	if (m_bEnbelope)
	{
		//	Calculate the rate of attack
		LONG	AttackRate = 0;
		ULONG	AttackTime = max(1, m_envelope.AttackTime);
		if (CurrentPos < AttackTime)
		{
			AttackRate = (AttackTime - CurrentPos) * 100 / AttackTime;
		}

		//	Calculate the percentage of fades
		LONG	FadeRate = 0;
		ULONG	FadeTime = max(1, m_envelope.FadeTime);
		ULONG	FadePos = Duration - FadeTime;
		if (FadePos < CurrentPos)
		{
			FadeRate = (CurrentPos - FadePos) * 100 / FadeTime;
		}

		//	Returns the calculated value
		*NormalRate = 100 - AttackRate - FadeRate;
		*AttackLevel = m_envelope.AttackLevel * AttackRate;
		*FadeLevel = m_envelope.FadeLevel * FadeRate;

	}
	else
	{

		*NormalRate = 100;
		*AttackLevel = 0;
		*FadeLevel = 0;
	}
}

//----------------------------------------------------------------------------------------------
//	CalcForce
//----------------------------------------------------------------------------------------------

VOID CEffect::CalcForce(
	ULONG		Duration
	, ULONG		CurrentPos
	, LONG		NormalRate
	, LONG		AttackLevel
	, LONG		FadeLevel
	, LONG* NormalLevel)
{
	LONG	Magnitude = 0;
	LONG	Period;
	LONG	R;
	LONG	Rate;

	FFBEType type = m_Type == FFBEType::ET_NONE ? m_report.EffectType : m_Type;

	//	Sort processing according to the type of effect
	switch (type)
	{
	case ET_SPRNG:
	case ET_DMPR:
	case ET_INRT:
	case ET_FRCTN:
		;
		break;

		//	Constant force
	case ET_CONST:
		//	Find the magnitude considering the envelope
		Magnitude = m_constantForce.Magnitude;
		Magnitude = (Magnitude * NormalRate + AttackLevel + FadeLevel) / 100;
		break;

		//	Custom force
	case ET_CSTM:
		;
		break;

		//	Periodic effect
	case ET_SQR:

		//	Find somewhere between 0 and 359 degrees from the time (milliseconds) and elapsed time of one cycle.
		Period = max(1, m_periodic.Period);
		R = (CurrentPos % Period) * 360 / Period;

		//	Calculate the phase
		R = (R + (m_periodic.Phase / 100)) % 360;

		//	Find the magnitude considering the envelope
		Magnitude = m_periodic.Magnitude;
		Magnitude = (Magnitude * NormalRate + AttackLevel + FadeLevel) / 100;

		//	Find the magnitude considering the square
		if (180 <= R)
		{
			Magnitude = Magnitude * -1;
		}

		//	Calculate the offset
		Magnitude = Magnitude + m_periodic.Offset;
		break;

	case ET_SINE:

		//	Find somewhere between 0 and 359 degrees from the time (milliseconds) and elapsed time of one cycle.
		Period = max(1, m_periodic.Period);
		R = (CurrentPos % Period) * 360 / Period;

		//	Calculate the phase
		R = (R + (m_periodic.Phase / 100)) % 360;

		//	Find the magnitude considering the envelope
		Magnitude = m_periodic.Magnitude;
		Magnitude = (Magnitude * NormalRate + AttackLevel + FadeLevel) / 100;

		//	Find the magnitude considering the square
		Magnitude = static_cast<LONG>(Magnitude * sin(R * 3.1415 / 180.0));

		//	Calculate the offset
		Magnitude = Magnitude + m_periodic.Offset;
		break;

	case ET_TRNGL:

		//	Find somewhere between 0 and 359 degrees from the time (milliseconds) and elapsed time of one cycle.
		Period = max(1, m_periodic.Period);
		R = (CurrentPos % Period) * 360 / Period;

		//	Calculate the phase
		R = (R + (m_periodic.Phase / 100)) % 360;

		//	Find the magnitude considering the envelope
		Magnitude = m_periodic.Magnitude;
		Magnitude = (Magnitude * NormalRate + AttackLevel + FadeLevel) / 100;

		//	Find the magnitude considering the triangular wave
		if (0 <= R && R < 90)
		{
			Magnitude = -Magnitude * (90 - R) / 90;
		}
		if (90 <= R && R < 180)
		{
			Magnitude = Magnitude * (R - 90) / 90;
		}
		if (180 <= R && R < 270)
		{
			Magnitude = Magnitude * (90 - (R - 180)) / 90;
		}
		if (270 <= R && R < 360)
		{
			Magnitude = -Magnitude * (R - 270) / 90;
		}
		//	Calculate the offset
		Magnitude = Magnitude + m_periodic.Offset;
		break;

	case ET_STUP:

		//	Find somewhere between 0 and 359 degrees from the time (milliseconds) and elapsed time of one cycle.
		Period = max(1, m_periodic.Period);
		R = (CurrentPos % Period) * 360 / Period;

		//	Calculate the phase
		R = (R + (m_periodic.Phase / 100)) % 360;

		//	Find the magnitude considering the envelope
		Magnitude = m_periodic.Magnitude;
		Magnitude = (Magnitude * NormalRate + AttackLevel + FadeLevel) / 100;

		//	Finding a magnitude that takes up saw teeth into consideration
		if (0 <= R && R < 180)
		{
			Magnitude = -Magnitude * (180 - R) / 180;
		}
		if (180 <= R && R < 360)
		{
			Magnitude = Magnitude * (R - 180) / 180;
		}

		//	Calculate the offset
		Magnitude = Magnitude + m_periodic.Offset;
		break;

	case ET_STDN:

		//	Find somewhere between 0 and 359 degrees from the time (milliseconds) and elapsed time of one cycle.
		Period = max(1, m_periodic.Period);
		R = (CurrentPos % Period) * 360 / Period;

		//	Calculate the phase
		R = (R + (m_periodic.Phase / 100)) % 360;

		//	Find the magnitude considering the envelope
		Magnitude = m_periodic.Magnitude;
		Magnitude = (Magnitude * NormalRate + AttackLevel + FadeLevel) / 100;

		//	Finding a magnitude that takes down feathers into consideration
		if (0 <= R && R < 180)
		{
			Magnitude = Magnitude * (180 - R) / 180;
		}
		if (180 <= R && R < 360)
		{
			Magnitude = -Magnitude * (R - 180) / 180;
		}

		//	Calculate the offset
		Magnitude = Magnitude + m_periodic.Offset;
		break;

		//	Inclined force
	case ET_RAMP:

		//	Calculate the ratio of start point and end point
		Rate = (Duration - CurrentPos) * 100
			/ max(1, m_report.Duration);

		//	Find the magnitude considering the envelope
		Magnitude = (m_rampForce.Start * Rate
			+ m_rampForce.End * (100 - Rate)) / 100;
		Magnitude = (Magnitude * NormalRate + AttackLevel + FadeLevel) / 100;
		break;
	}

	//	Returns a force that takes gain into account
	*NormalLevel = Magnitude * m_report.Gain / 0xFF;
}
