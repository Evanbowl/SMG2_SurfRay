#pragma once

#include "syati.h"

class SurfRayConst {
public:
    bool mIsRaceMode; // * new
    bool mIsStickControl; // * new
    bool mIsDiveEnabled; // * new
    f32 mDistancePlayerNear;
    f32 mGravity; // ! undocumented
    f32 mGroundReboundRate; // ! undocumented
    f32 mWallReboundRate; // ! undocumented
    f32 mReboundSpeedMin; // ! undocumented
    f32 mRunAccel;
    f32 mRunSpeedMax;
    f32 mFlyUpSpeedMaxY; // ! undocumented
    f32 mFallSpeedMaxY; // ! undocumented
    f32 mRunGroundFrictionRate; // ! undocumented
    f32 mRunAirFrictionRate; // ! undocumented
    f32 mSpeedToRumble;
    f32 mWaterFriction; // ! undocumented
    f32 mWaterGravity; // ! undocumented
    f32 mWaterPressureRate; // ! undocumented
    f32 mWaterWaveNrmAccelRate; // ! undocumented
    f32 mWaterUpSideSpeedMax; // ! undocumented
    f32 mWaterBottomReboundRate; // ! undocumented
    f32 mWaterUpperPosOffset; // ! undocumented
    f32 mWaterJudgeFront; // ! undocumented
    f32 mWaterJudgeUp; // ! undocumented
    f32 mWaterJudgeWidth; // ! undocumented
    f32 mUpSideGroundFrictionRate; // ! undocumented
    f32 mUpSideAirFrictionRate; // ! undocumented
    f32 mUpSideSpeedMin; // ! undocumented
    s32 mStepEnableJumpAtAir;
    s32 mStepToFallAtAir;
    f32 mJumpAccelMinY; // ! undocumented
    f32 mJumpAccelMaxY; // ! undocumented
    f32 mJumpSpeedMaxY;
    f32 mJumpSpeedHigh;
    f32 mRunSpeedMinToRotate;
    f32 mRotateAccelRate; // ! undocumented
    f32 mPadAccelAddRateZ; // ! undocumented
    f32 mPadAccelClamp; // ! undocumented
    f32 mPadAccelInvalidMaxZ; // ! undocumented
    f32 mPadAccelInvalidMinX; // ! undocumented
    f32 mPadAccelInvalidFrictionRate; // ! undocumented
    f32 mRotateSpeedFrictionRate; // ! undocumented
    f32 mRotateFrictionRate; // ! undocumented
    f32 mRotateSpeedMin; // ! undocumented
    f32 mRotateSpeedMax; // ! undocumented
    f32 mRotateMaxZ;
    f32 mRotateSpeedRate; // ! undocumented
    f32 mBlendRatioAxisUpAir;
    f32 mBlendRatioAxisUpGround;
    f32 mBlendRatioAxisFrontWall;
    f32 mPlayerPosOffsetY;
    f32 mPlayerPosOffsetZ;
    f32 mRiderRotateInterpolateRate; // ! undocumented
    f32 mRiderRotateRateScale; // ! undocumented
    f32 mTwistStartDiffMin;
    f32 mBtkSpeedMin;
    f32 mBtkSpeedMax;
    f32 mBtkSpeedRate;
    f32 mShadowAlphaMax;
    f32 mShadowAlphaSpeed;
    f32 mSpeedToEmitEffect;
    f32 mSpeedToEmitEffectFast;
    f32 mMoveSeRotRate; // ! undocumented
    f32 mMoveSe0StartSpeed;
    f32 mMoveSe1StartSpeed;
    f32 mMoveSe2StartSpeed;
    f32 mMoveSe3StartSpeed;
    f32 mMoveSe3MaxSpeed;
    f32 mWindSeStartSpeed;
    f32 mWindSeMaxSpeed;
    f32 mJumpInSoundMaxSpeed; // ! undocumented
    f32 mHitSoundStartVelocity;
    f32 mVelocityUpSideScale; // ! undocumented
    f32 mRotateZFrictionRate; // ! undocumented
    f32 mMarioAnimeBlendRate; // ! undocumented
    f32 mDiveAccel; // * new
    f32 mDiveSpeedMax; // * new
    f32 mAttackSpeedMax; // * new

    void initDefault();
    void initFromTable(s32 idx);
};