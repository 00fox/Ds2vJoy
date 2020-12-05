//移植
//	Force Feedback Driver for XInput
#include	"..\stdafx.h"
#include	"effect.h"

//----------------------------------------------------------------------------------------------
//	CEffect
//----------------------------------------------------------------------------------------------
CEffect::CEffect()
	:m_Type(FFBEType::ET_NONE)
{
	//	状態
	m_Status	= 0;
	//	再生回数
	m_PlayCount	= 0;
	//	再生時刻
	m_StartTime	= 0;
}

//----------------------------------------------------------------------------------------------
//	Calc
//----------------------------------------------------------------------------------------------
BOOL CEffect::Calc(
	  LONG *	LeftLevel
	, LONG *	RightLevel
	, double	CurrentTime)
{
	if (m_Status == FALSE)
		return FALSE;
	//	エフェクトの再生時間、開始時刻、終了時刻、現在時刻を算出する
	ULONG	Duration	= max( 1, m_report.Duration  );
	double	EndTime		= DBL_MAX;
	if( m_PlayCount != -1 && Duration != 0xFFFF)
	{
		EndTime	= m_StartTime + Duration * m_PlayCount;
	}

	//	エフェクトは再生中？
	if( CurrentTime <= EndTime )
	{
		
		//	エンベロープを計算する
		LONG	NormalRate;
		LONG	AttackLevel;
		LONG	FadeLevel;
		CalcEnvelope(
			 Duration
			,static_cast<ULONG>( CurrentTime - m_StartTime) % Duration
			,&NormalRate
			,&AttackLevel
			,&FadeLevel );

		//	フォースを計算する
		LONG	NormalLevel;
		LONG	WorkLeftLevel;
		LONG	WorkRightLevel;
		CalcForce(
			 Duration
			, static_cast<ULONG>( CurrentTime - m_StartTime) % Duration
			,NormalRate
			,AttackLevel
			,FadeLevel
			,&NormalLevel );

		//	フォースの正負を調整する
		WorkLeftLevel	= (NormalLevel > 0) ? NormalLevel : -NormalLevel;
		WorkRightLevel	= (NormalLevel > 0) ? NormalLevel : -NormalLevel;

		//	フォースの上限を調整する
		WorkLeftLevel	= min(0xFF, WorkLeftLevel * 0xFF / 10000 );
		WorkRightLevel	= min(0xFF, WorkRightLevel * 0xFF / 10000 );

		//	フォースを加算する
		*LeftLevel	= *LeftLevel + WorkLeftLevel;
		*RightLevel	= *RightLevel + WorkRightLevel;
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
	,ULONG	CurrentPos
	,LONG *	NormalRate
	,LONG *	AttackLevel
	,LONG *	FadeLevel )
{
	//	エンベロープを計算する
	if( m_bEnbelope )
	{
		//	アタックの割合を算出する
		LONG	AttackRate	= 0;
		ULONG	AttackTime	= max( 1, m_envelope.AttackTime  );
		if( CurrentPos < AttackTime )
		{
			AttackRate	= ( AttackTime - CurrentPos ) * 100 / AttackTime;
		}
		//	フェードの割合を算出する
		LONG	FadeRate	= 0;
		ULONG	FadeTime	= max( 1, m_envelope.FadeTime  );
		ULONG	FadePos		= Duration - FadeTime;
		if( FadePos < CurrentPos )
		{
			FadeRate	= ( CurrentPos - FadePos ) * 100 / FadeTime;
		}
		//	算出した値を返す
		*NormalRate		= 100 - AttackRate - FadeRate;
		*AttackLevel	= m_envelope.AttackLevel * AttackRate;
		*FadeLevel		= m_envelope.FadeLevel * FadeRate;
	} else {
		*NormalRate		= 100;
		*AttackLevel	= 0;
		*FadeLevel		= 0;
	}
}

//----------------------------------------------------------------------------------------------
//	CalcForce
//----------------------------------------------------------------------------------------------
VOID CEffect::CalcForce(
	 ULONG		Duration
	,ULONG		CurrentPos
	,LONG		NormalRate
	,LONG		AttackLevel
	,LONG		FadeLevel
	,LONG *		NormalLevel )
{
	//	変数宣言
	LONG	Magnitude	= 0;
	LONG	Period;
	LONG	R;
	LONG	Rate;

	FFBEType type = m_Type == FFBEType::ET_NONE ? m_report.EffectType : m_Type;
	//	エフェクトの種類によって処理を振り分ける
	switch(type)
	{
		//	条件
		case ET_SPRNG:
		case ET_DMPR:
		case ET_INRT:
		case ET_FRCTN:
			;
			break;

		//	コンスタント フォース
		case ET_CONST:
			//	エンベロープを考慮したマグニチュードを求める
			Magnitude = m_constantForce.Magnitude;
			Magnitude	= ( Magnitude * NormalRate + AttackLevel + FadeLevel ) / 100;
			break;

		//	カスタム フォース
		case ET_CSTM:
			;
			break;

		//	周期的エフェクト
		case ET_SQR:
			//	１周期の時間（ミリ秒）と経過時間から 0 ～ 359 度のどこかを求める
			Period	= max( 1, m_periodic.Period );
			R		= ( CurrentPos % Period ) * 360 / Period;
			//	フェーズを計算する
			R	= ( R + ( m_periodic.Phase / 100 ) ) % 360;
			//	エンベロープを考慮したマグニチュードを求める
			Magnitude	= m_periodic.Magnitude;
			Magnitude	= ( Magnitude * NormalRate + AttackLevel + FadeLevel ) / 100;
			//	正方形を考慮したマグニチュードを求める
			if( 180 <= R )
			{
				Magnitude	= Magnitude * -1;
			}
			//	オフセットを計算する
			Magnitude	= Magnitude + m_periodic.Offset;
			break;

		case ET_SINE:
			//	１周期の時間（ミリ秒）と経過時間から 0 ～ 359 度のどこかを求める
			Period	= max( 1, m_periodic.Period );
			R		= ( CurrentPos % Period ) * 360 / Period;
			//	フェーズを計算する
			R		= ( R + ( m_periodic.Phase / 100 ) ) % 360;
			//	エンベロープを考慮したマグニチュードを求める
			Magnitude	= m_periodic.Magnitude;
			Magnitude	= ( Magnitude * NormalRate + AttackLevel + FadeLevel ) / 100;
			//	正弦波を考慮したマグニチュードを求める
			Magnitude	= static_cast<LONG>( Magnitude * sin( R * 3.1415 / 180.0 ) );
			//	オフセットを計算する
			Magnitude	= Magnitude + m_periodic.Offset;
			break;

		case ET_TRNGL:
			//	１周期の時間（ミリ秒）と経過時間から 0 ～ 359 度のどこかを求める
			Period	= max( 1, m_periodic.Period );
			R		= ( CurrentPos % Period ) * 360 / Period;
			//	フェーズを計算する
			R		= ( R + ( m_periodic.Phase / 100 ) ) % 360;
			//	エンベロープを考慮したマグニチュードを求める
			Magnitude	= m_periodic.Magnitude;
			Magnitude	= ( Magnitude * NormalRate + AttackLevel + FadeLevel ) / 100;
			//	三角波を考慮したマグニチュードを求める
			if( 0 <= R && R < 90 )
			{
				Magnitude	= -Magnitude * ( 90 - R ) / 90;
			}
			if( 90 <= R && R < 180 )
			{
				Magnitude	= Magnitude * ( R - 90 ) / 90;
			}
			if( 180 <= R && R < 270 )
			{
				Magnitude	= Magnitude * ( 90 - ( R - 180 ) ) / 90;
			}
			if( 270 <= R && R < 360 )
			{
				Magnitude	= -Magnitude * ( R - 270 ) / 90;
			}
			//	オフセットを計算する
			Magnitude	= Magnitude + m_periodic.Offset;
			break;

		case ET_STUP:
			//	１周期の時間（ミリ秒）と経過時間から 0 ～ 359 度のどこかを求める
			Period	= max( 1, m_periodic.Period );
			R		= ( CurrentPos % Period ) * 360 / Period;
			//	フェーズを計算する
			R		= ( R + ( m_periodic.Phase / 100 ) ) % 360;
			//	エンベロープを考慮したマグニチュードを求める
			Magnitude	= m_periodic.Magnitude;
			Magnitude	= ( Magnitude * NormalRate + AttackLevel + FadeLevel ) / 100;
			//	アップ鋸歯を考慮したマグニチュードを求める
			if( 0 <= R && R < 180 )
			{
				Magnitude	= -Magnitude * ( 180 - R ) / 180;
			}
			if( 180 <= R && R < 360 )
			{
				Magnitude	= Magnitude * ( R - 180 ) / 180;
			}
			//	オフセットを計算する
			Magnitude	= Magnitude + m_periodic.Offset;
			break;

		case ET_STDN:
			//	１周期の時間（ミリ秒）と経過時間から 0 ～ 359 度のどこかを求める
			Period	= max( 1, m_periodic.Period );
			R		= ( CurrentPos % Period ) * 360 / Period;
			//	フェーズを計算する
			R		= ( R + ( m_periodic.Phase / 100 ) ) % 360;
			//	エンベロープを考慮したマグニチュードを求める
			Magnitude	= m_periodic.Magnitude;
			Magnitude	= ( Magnitude * NormalRate + AttackLevel + FadeLevel ) / 100;
			//	ダウン鋸歯を考慮したマグニチュードを求める
			if( 0 <= R && R < 180 )
			{
				Magnitude	= Magnitude * ( 180 - R ) / 180;
			}
			if( 180 <= R && R < 360 )
			{
				Magnitude	= -Magnitude * ( R - 180 ) / 180;
			}
			//	オフセットを計算する
			Magnitude	= Magnitude + m_periodic.Offset;
			break;

		//	傾斜フォース
		case ET_RAMP:
			//	始点、終点の割合を算出する
			Rate		= ( Duration - CurrentPos ) * 100
						/ max( 1, m_report.Duration  );
			//	エンベロープを考慮したマグニチュードを求める
			Magnitude	= ( m_rampForce.Start * Rate
							+ m_rampForce.End * ( 100 - Rate ) ) / 100;
			Magnitude	= ( Magnitude * NormalRate + AttackLevel + FadeLevel ) / 100;
			break;
	}

	//	ゲインを考慮したフォースを返す
	*NormalLevel	= Magnitude * m_report.Gain / 0xFF;
}
