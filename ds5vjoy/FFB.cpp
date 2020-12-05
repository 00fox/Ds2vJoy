//移植
#include "stdafx.h"
#include "FFB.h"

void FFB::callback(PVOID data, PVOID userdata)
{
	if (userdata == 0)
		return;
	FFB *ffb = (FFB*)userdata;
	ffb->_callback((FFB_DATA *)data);
}

void FFB::_callback(FFB_DATA *data)
{

	FFBPType	Type;
	if (ERROR_SUCCESS != Ffb_h_Type(data, &Type))
		return;
	int BlockIndex=-1;
	Ffb_h_EBI(data, &BlockIndex);
		
	CEffect * effect=NULL;
	if(BlockIndex!=-1)
		effect = &m_effects[BlockIndex];
	std::lock_guard<std::mutex> lock(m_mutex);

	switch (Type)
	{
	case PT_EFFREP:
#pragma warning( push )
#pragma warning( disable : 4996 )
		if (ERROR_SUCCESS != Ffb_h_Eff_Report(data, &effect->m_report))
			break;
#pragma warning( pop )
		break;
	case PT_ENVREP:
		if (ERROR_SUCCESS != Ffb_h_Eff_Envlp(data, &effect->m_envelope))
			break;
		effect->m_bEnbelope = true;
		effect->m_envelope.AttackLevel = static_cast<LONG>(static_cast<__int16>(effect->m_envelope.AttackLevel));
		effect->m_envelope.FadeLevel = static_cast<LONG>(static_cast<__int16>(effect->m_envelope.FadeLevel));
		break;
	case PT_CONDREP:
		//Condition Report
		break;
	case PT_PRIDREP:
		if (ERROR_SUCCESS != Ffb_h_Eff_Period(data, &effect->m_periodic))
			break;
		effect->m_periodic.Offset = static_cast<LONG>(static_cast<__int16>(effect->m_periodic.Offset));
		break;
	case PT_CONSTREP:
		if (ERROR_SUCCESS != Ffb_h_Eff_Constant(data, &effect->m_constantForce))
			break;
		effect->m_constantForce.Magnitude = static_cast<LONG>(static_cast<__int16>(effect->m_constantForce.Magnitude));
		break;
	case PT_RAMPREP:
		if (ERROR_SUCCESS != Ffb_h_Eff_Ramp(data, &effect->m_rampForce))
			break;
		effect->m_rampForce.Start = static_cast<LONG>(static_cast<__int16>(effect->m_rampForce.Start));
		effect->m_rampForce.End = static_cast<LONG>(static_cast<__int16>(effect->m_rampForce.End));
		break;
	case PT_CSTMREP:
		//Custom Force Data Report
		break;
	case PT_SMPLREP:
		//-Download Force Sample
		break;
	case PT_EFOPREP:
		//Effect Operation Report
		_operation(data);
		break;
	case PT_BLKFRREP:
		//PID Block Free Report
		m_effects.erase(BlockIndex);
		break;
	case PT_CTRLREP:
		//-PID Device Contro
		_ctrl(data);
		break;
	case PT_GAINREP:
		//-Device Gain Report
		if (ERROR_SUCCESS != Ffb_h_DevGain(data, &m_Gain))
			break;
		break;
	case PT_SETCREP:
		//Set Custom Force Report
		break;
	case PT_NEWEFREP:
	{
		/*
		CEffect neweffect;
		if (ERROR_SUCCESS != Ffb_h_EffNew(data, &neweffect.m_Type))
			break;
		*/
		break;
	}
	case PT_BLKLDREP:
		//Block Load Report
		break;
	case PT_POOLREP:
		//-PID Pool Report
		break;
	}

}

void FFB::_ctrl(FFB_DATA *data)
{
	FFB_CTRL	control;
	if (ERROR_SUCCESS != Ffb_h_DevCtrl(data, &control))
		return;
	switch (control)
	{
	case CTRL_ENACT:
		//アクチュエータを有効にするEnable Actuators
		m_bActuator = true;
		break;
	case CTRL_DISACT:
		//アクチュエータを無効にするDisable Actuators
		m_bActuator = false;
		break;
	case CTRL_STOPALL:
		//全てのエフェクトの再生を停止するStop All Effects
		for (auto &kv : m_effects) {
			kv.second.m_Status = FALSE;
		}
		break;
	case CTRL_DEVRST:
		//全てのエフェクトを削除するDevice Reset
		m_effects.clear();
		break;
	case CTRL_DEVPAUSE:
		//再生を一時停止するDevice Pause
		for (auto &kv : m_effects) {
			kv.second.m_Status = FALSE;
		}
		m_bPaused = true;
		m_dwPausedTime = getTime();
		break;
	case CTRL_DEVCONT:
		//一時停止を解除するDevice Continue
		if (m_bPaused) {
			m_dwPausedTime = getTime() - m_dwPausedTime;
			for (auto &kv : m_effects) {
				if (kv.second.m_Status == FALSE) {
					kv.second.m_StartTime += m_dwPausedTime;
					kv.second.m_Status = TRUE;
				}
			}
			m_bPaused = false;
		}
		break;
	}
}

void FFB::_operation(FFB_DATA *data)
{
	FFB_EFF_OP op;
	if (ERROR_SUCCESS != Ffb_h_EffOp(data, &op))
		return;
	CEffect*effect = &m_effects[op.EffectBlockIndex];
	switch (op.EffectOp)
	{
	case EFF_SOLO:
		//Effect Solo Start
		for (auto &kv : m_effects) {
			kv.second.m_Status = FALSE;
		}
	case EFF_START:
		//Effect Start
		effect->m_StartTime = getTime();
		effect->m_Status = TRUE;
		effect->m_PlayCount = op.LoopCount;
		m_bStoped = false;
		m_bPaused = false;
		break;
	case EFF_STOP:
		//Effect Stop
		effect->m_Status = FALSE;
		break;
	}
}

double FFB::getTime()
{
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	return (double)(t.QuadPart - m_gt_start.QuadPart) / m_gt_ms;
}



bool FFB::Calc(BYTE * _left, BYTE * _right)
{
	LONG left = 0, right = 0;
	if (m_bActuator && !m_bStoped && !m_bPaused) {
		bool playing = false;
		double currentTime = getTime();
		std::lock_guard<std::mutex> lock(m_mutex);
		for (auto &kv : m_effects) {
			if (kv.second.Calc(&left, &right, currentTime))
				playing = true;
		}
		if (!playing) {
			m_bStoped = true;
		}
		if (left > 0xFF) left = 0xFF;
		if (right > 0xFF) right = 0xFF;
		left = left * m_Gain / 0xFF;
		right = right * m_Gain / 0xFF;
	}
	if (m_lastLeft != left || m_lastRight != right) {
		*_left = m_lastLeft = static_cast<BYTE>(left);
		*_right = m_lastRight = static_cast<BYTE>(right);
		return true;
	}
	return false;
}

FFB::FFB()
	:m_bActuator(true)
	,m_bPaused(false)
	,m_bStoped(true)
	,m_Gain(0xFF)
{
	LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
	m_gt_ms = static_cast<double>(f.QuadPart) / 1000.0;
	QueryPerformanceCounter(&m_gt_start);
}

FFB::~FFB()
{
}
