//移植
//	Force Feedback Driver for XInput

#pragma	once

//----------------------------------------------------------------------------------------------
//	クラス
//----------------------------------------------------------------------------------------------

class CEffect
{

public:

	//	コンストラクタ
	CEffect();

	//	エフェクトを計算する
	BOOL Calc(LONG  *, LONG  *, double CurrentTime);

	//	種類
	FFBEType			m_Type;
	//	DIEFFECT 構造体
	FFB_EFF_REPORT m_report = { 0 };

	//	DIENVELOPE 構造体
	FFB_EFF_ENVLP m_envelope = { 0 };
	bool m_bEnbelope;

	//	DICONSTANTFORCE 構造体
	FFB_EFF_CONSTANT m_constantForce = { 0 };

	//	DIPERIODIC 構造体
	FFB_EFF_PERIOD m_periodic = { 0 };

	//	DIRAMPFORCE 構造体
	FFB_EFF_RAMP m_rampForce = { 0 };

	//	状態
	DWORD			m_Status;
	//	再生回数
	DWORD			m_PlayCount;
	//	再生時刻
	double			m_StartTime;

private:

	//	エンベロープを計算する
	VOID CalcEnvelope( ULONG, ULONG, LONG *, LONG *, LONG * );
	//	フォースを計算する
	VOID CalcForce( ULONG, ULONG, LONG, LONG, LONG, LONG * );

protected:

};
