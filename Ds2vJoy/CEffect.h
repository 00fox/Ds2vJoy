#pragma	once

//----------------------------------------------------------------------------------------------
//	Transplant
//	Force Feedback Driver for XInput
//----------------------------------------------------------------------------------------------

class CEffect
{
public:
	//	Constructor
	CEffect();

	//	Calculate the effect
	BOOL Calc(LONG*, LONG*, double CurrentTime);

	//	Type
	FFBEType			m_Type;
	//	DIEFFECT
	FFB_EFF_REPORT m_report = { 0 };

	//	DIENVELOPE
	FFB_EFF_ENVLP m_envelope = { 0 };
	bool m_bEnbelope;

	//	DICONSTANTFORCE
	FFB_EFF_CONSTANT m_constantForce = { 0 };

	//	DIPERIODIC
	FFB_EFF_PERIOD m_periodic = { 0 };

	//	DIRAMPFORCE
	FFB_EFF_RAMP m_rampForce = { 0 };

	//	status
	DWORD m_Status;
	//	View
	unsigned long m_PlayCount;
	//	Rebirth moment
	double m_StartTime;

private:
	//	Calculate the envelope
	VOID CalcEnvelope(ULONG, ULONG, LONG*, LONG*, LONG*);
	//	Calculate the force
	VOID CalcForce(ULONG, ULONG, LONG, LONG, LONG, LONG*);

protected:
};
