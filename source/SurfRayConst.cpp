#include "SurfRayConst.h"

void SurfRayConst::initDefault() {
    mIsRaceMode = false;
    mIsStickControl = false;
    mIsDiveEnabled = false;
    mDistancePlayerNear = 1300.0f;
    // mGravity
    // mGroundReboundRate
    // mWallReboundRate
    // mReboundSpeedMin
    mRunAccel = 0.5f;
    mRunSpeedMax = 40.0f;
    // mFlyUpSpeedMaxY
    // mFallSpeedMaxY
    // mRunGroundFrictionRate
    // mRunAirFrictionRate
    mSpeedToRumble = 5.0f;
    // mWaterFriction
    // mWaterGravity
    // mWaterPressureRate
    // mWaterWaveNrmAccelRate
    // mWaterUpSideSpeedMax
    // mWaterBottomReboundRate
    // mWaterUpperPosOffset
    // mWaterJudgeFront
    // mWaterJudgeUp
    // mWaterJudgeWidth
    // mUpSideGroundFrictionRate
    // mUpSideAirFrictionRate
    // mUpSideSpeedMin
    mStepEnableJumpAtAir = 15;
    mStepToFallAtAir = 45;
    // mJumpAccelMinY
    // mJumpAccelMaxY
    mJumpSpeedMaxY = 25.0f;
    mJumpSpeedHigh = 23.0f;
    mRunSpeedMinToRotate = 3.0f;
    // mRotateAccelRate
    // mPadAccelAddRateZ
    // mPadAccelClamp
    // mPadAccelInvalidMaxZ
    // mPadAccelInvalidMinX
    // mPadAccelInvalidFrictionRate
    // mRotateSpeedFrictionRate
    // mRotateFrictionRate
    // mRotateSpeedMin
    // mRotateSpeedMax
    mRotateMaxZ = 70.0f;
    // mRotateSpeedRate
    mBlendRatioAxisUpAir = 0.02f;
    mBlendRatioAxisUpGround = 0.1f;
    mBlendRatioAxisFrontWall = 0.1f;
    mPlayerPosOffsetY = 55.0f;
    mPlayerPosOffsetZ = 12.0f;
    // mRiderRotateInterpolateRate
    // mRiderRotateRateScale
    mTwistStartDiffMin = 0.2f;
    mBtkSpeedMin = 1.0f;
    mBtkSpeedMax = 4.0f;
    mBtkSpeedRate = 0.4f;
    mShadowAlphaMax = 64.0f;
    mShadowAlphaSpeed = 10.0f;
    mSpeedToEmitEffect = 6.0f;
    mSpeedToEmitEffectFast = 20.0f;
    // mMoveSeRotRate
    mMoveSe0StartSpeed = 2.5f;
    mMoveSe1StartSpeed = 7.5f;
    mMoveSe2StartSpeed = 14.0f;
    mMoveSe3StartSpeed = 25.0f;
    mMoveSe3MaxSpeed = 35.0f;
    mWindSeStartSpeed = 32.0f;
    mWindSeMaxSpeed = 50.0f;
    // mJumpInSoundMaxSpeed
    mHitSoundStartVelocity = -10.0;
    // mVelocityUpSideScale
    // mRotateZFrictionRate
    // mMarioAnimeBlendRate
    mDiveAccel = 0.1f;
    mDiveSpeedMax = 1.0f;
    mAttackSpeedMax = 20.0f;
}

void SurfRayConst::initFromTable(s32 idx) {
    const JMapInfo *pInfo = MR::tryCreateCsvParser("/ObjectData/SurfRayConst.arc", "/SurfRayConst.bcsv");
    JMapInfoIter iter(pInfo, idx);
    iter.getValue("IsRaceMode", &mIsRaceMode);
    iter.getValue("IsStickControl", &mIsStickControl);
    iter.getValue("IsDiveEnabled", &mIsDiveEnabled);
    iter.getValue("DistancePlayerNear", &mDistancePlayerNear);
    iter.getValue("Gravity", &mGravity);
    iter.getValue("GroundReboundRate", &mGroundReboundRate);
    iter.getValue("WallReboundRate", &mWallReboundRate);
    iter.getValue("ReboundSpeedMin", &mReboundSpeedMin);
    iter.getValue("RunAccel", &mRunAccel);
    iter.getValue("RunSpeedMax", &mRunSpeedMax);
    iter.getValue("FlyUpSpeedMaxY", &mFlyUpSpeedMaxY);
    iter.getValue("FallSpeedMaxY", &mFallSpeedMaxY);
    iter.getValue("RunGroundFrictionRate", &mRunGroundFrictionRate);
    iter.getValue("RunAirFrictionRate", &mRunAirFrictionRate);
    iter.getValue("SpeedToRumble", &mSpeedToRumble);
    iter.getValue("WaterFriction", &mWaterFriction);
    iter.getValue("WaterGravity", &mWaterGravity);
    iter.getValue("WaterPressureRate", &mWaterPressureRate);
    iter.getValue("WaterWaveNrmAccelRate", &mWaterWaveNrmAccelRate);
    iter.getValue("WaterUpSideSpeedMax", &mWaterUpSideSpeedMax);
    iter.getValue("WaterBottomReboundRate", &mWaterBottomReboundRate);
    iter.getValue("WaterUpperPosOffset", &mWaterUpperPosOffset);
    iter.getValue("WaterJudgeFront", &mWaterJudgeFront);
    iter.getValue("WaterJudgeUp", &mWaterJudgeUp);
    iter.getValue("WaterJudgeWidth", &mWaterJudgeWidth);
    iter.getValue("UpSideGroundFrictionRate", &mUpSideGroundFrictionRate);
    iter.getValue("UpSideAirFrictionRate", &mUpSideAirFrictionRate);
    iter.getValue("UpSideSpeedMin", &mUpSideSpeedMin);
    iter.getValue("StepEnableJumpAtAir", &mStepEnableJumpAtAir);
    iter.getValue("StepToFallAtAir", &mStepToFallAtAir);
    iter.getValue("JumpAccelMinY", &mJumpAccelMinY);
    iter.getValue("JumpAccelMaxY", &mJumpAccelMaxY);
    iter.getValue("JumpSpeedMaxY", &mJumpSpeedMaxY);
    iter.getValue("JumpSpeedHigh", &mJumpSpeedHigh);
    iter.getValue("RunSpeedMinToRotate", &mRunSpeedMinToRotate);
    iter.getValue("RotateAccelRate", &mRotateAccelRate);
    iter.getValue("PadAccelAddRateZ", &mPadAccelAddRateZ);
    iter.getValue("PadAccelClamp", &mPadAccelClamp);
    iter.getValue("PadAccelInvalidMaxZ", &mPadAccelInvalidMaxZ);
    iter.getValue("PadAccelInvalidMinX", &mPadAccelInvalidMinX);
    iter.getValue("PadAccelInvalidFrictionRate", &mPadAccelInvalidFrictionRate);
    iter.getValue("RotateSpeedFrictionRate", &mRotateSpeedFrictionRate);
    iter.getValue("RotateFrictionRate", &mRotateFrictionRate);
    iter.getValue("RotateSpeedMin", &mRotateSpeedMin);
    iter.getValue("RotateSpeedMax", &mRotateSpeedMax);
    iter.getValue("RotateMaxZ", &mRotateMaxZ);
    iter.getValue("RotateSpeedRate", &mRotateSpeedRate);
    iter.getValue("BlendRatioAxisUpAir", &mBlendRatioAxisUpAir);
    iter.getValue("BlendRatioAxisUpGround", &mBlendRatioAxisUpGround);
    iter.getValue("BlendRatioAxisFrontWall", &mBlendRatioAxisFrontWall);
    iter.getValue("PlayerPosOffsetY", &mPlayerPosOffsetY);
    iter.getValue("PlayerPosOffsetZ", &mPlayerPosOffsetZ);
    iter.getValue("RiderRotateInterpolateRate", &mRiderRotateInterpolateRate);
    iter.getValue("RiderRotateRateScale", &mRiderRotateRateScale);
    iter.getValue("TwistStartDiffMin", &mTwistStartDiffMin);
    iter.getValue("BtkSpeedMin", &mBtkSpeedMin);
    iter.getValue("BtkSpeedMax", &mBtkSpeedMax);
    iter.getValue("BtkSpeedRate", &mBtkSpeedRate);
    iter.getValue("ShadowAlphaMax", &mShadowAlphaMax);
    iter.getValue("ShadowAlphaSpeed", &mShadowAlphaSpeed);
    iter.getValue("SpeedToEmitEffect", &mSpeedToEmitEffect);
    iter.getValue("SpeedToEmitEffectFast", &mSpeedToEmitEffectFast);
    iter.getValue("MoveSeRotRate", &mMoveSeRotRate);
    iter.getValue("MoveSe0StartSpeed", &mMoveSe0StartSpeed);
    iter.getValue("MoveSe1StartSpeed", &mMoveSe1StartSpeed);
    iter.getValue("MoveSe2StartSpeed", &mMoveSe2StartSpeed);
    iter.getValue("MoveSe3StartSpeed", &mMoveSe3StartSpeed);
    iter.getValue("MoveSe3MaxSpeed", &mMoveSe3MaxSpeed);
    iter.getValue("WindSeStartSpeed", &mWindSeStartSpeed);
    iter.getValue("WindSeMaxSpeed", &mWindSeMaxSpeed);
    iter.getValue("JumpInSoundMaxSpeed", &mJumpInSoundMaxSpeed);
    iter.getValue("HitSoundStartVelocity", &mHitSoundStartVelocity);
    iter.getValue("VelocityUpSideScale", &mVelocityUpSideScale);
    iter.getValue("RotateZFrictionRate", &mRotateZFrictionRate);
    iter.getValue("MarioAnimeBlendRate", &mMarioAnimeBlendRate);
    iter.getValue("DiveAccel", &mDiveAccel);
    iter.getValue("DiveSpeedMax", &mDiveSpeedMax);
    iter.getValue("AttackSpeedMax", &mAttackSpeedMax);
}