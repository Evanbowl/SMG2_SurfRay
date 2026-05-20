#pragma once

#include "syati.h"
#include "SurfRayConst.h"

class ActorJointCtrl;
class ProjmapEffectMtxSetter;

enum SurfRayBehavior {
    SURF_RAY_BHV_NONE       = 0x0,
    SURF_RAY_BHV_RACE       = 0x1,
    SURF_RAY_BHV_STICK_CTRL = 0x2,
    SURF_RAY_BHV_MOVE_DIVE  = 0x4,
};

class SurfRay : public LiveActor {
public:
    SurfRay(const char* pName, s32 padChannel = 0);

    virtual void init(const JMapInfoIter &);
    virtual void control();
    virtual void calcAndSetBaseMtx();
    virtual void attackSensor(HitSensor*, HitSensor*);
    virtual bool receiveMsgEnemyAttack(u32 msg, HitSensor *pSender, HitSensor *pReceiver);
    virtual bool receiveOtherMsg(u32, HitSensor*, HitSensor*);

    void exeWaitPlayer();
    void exeTurnToWait();
    void exeWait();
    void exeRideAccel();
    void exeRideAccelTwist();
    void exeRideFree();
    void exeRideFreeTwist();
    void exeRideJump();
    void exeRideJumpHigh();
    void exeRideFall();
    void exeRideLand();
    void exeTutorial();
    void exeWipeOut();
    void exeWipeIn();
    void exeReady();

    void resetAllInfo();

    bool updateRideAccel();
    bool updateRideFree();
    bool updateRide();
    void updateInfo();
    void updateToMap();
    void updateToWater();
    void updateAccel();
    void updateRotate();
    void updateSound();
    void updateRiderMtx();

    bool tryInWater();
    bool tryJumpOrFall();
    bool isTwistStart() const;
    bool isRotateStart() const;

    // New Functions
    void updateBoost();
    bool isUnderwater();
    bool tryDismount();
    void exePlayerExit();

    void updateDive();
    void updateEffect();
    void calcRotateAccel(TVec3f *pOut) const;

    bool canBind() const;

    /* 0x8C */ f32 mSurfSpeed;
    /* 0x90 */ f32 mOrthoSpeed;
    /* 0x94 */ TVec3f mOrthoVelocity;

    /* 0xA0 */ f32 mSteerRate;
    /* 0xA4 */ f32 mSteerAccel;

    /* 0xA8 */ TVec3f mFront;
    /* 0xB4 */ TVec3f mUp;
    /* 0xC0 */ TVec3f mSide;
    /* 0xCC */ TVec3f mBaseUp;    // base up vector for modification
    /* 0xD8 */ TVec3f mBaseSide;  // base side vector for modification
    /* 0xE4 */ TVec3f mGroundNormal;
    /* 0xF0 */ TVec3f mWarpPos;

    /* 0xFC */ LiveActor* mRider;

    /* 0x100 */ s32 mPadChannel;
    /* 0x104 */ f32 mRayTilt;
    /* 0x108 */ bool mInWater;
    /* 0x10C */ s32 mAirTime;
    /* 0x110 */ TVec3f mWaterNormal;
    /* 0x11C */ WaterInfo mWaterInfo;
    /* 0x16C */ TVec3f mWaterShadowPos;
    /* 0x178 */ f32 mShadowAlpha;

    /* 0x17C */ s32 mTwistBufferSize;
    /* 0x180 */ f32* mTwistBuffer;

    /* 0x184 */ bool mInTutorialArea;
    /* 0x185 */ bool mInTutorial;
    /* 0x188 */ s32 mLectureIdx;

    /* 0x18C */ TPos3f mEffectHostMtx;
    /* 0x1BC */ ActorJointCtrl* mActorJointCtrl;
    /* 0x1C0 */ ProjmapEffectMtxSetter* mProjmapFxMtxSetter;

    // New Members
    /* 0x1C4 */ SurfRayConst* mConst;
    /* 0x1C8 */ f32 mDiveSpeed;
    f32 mSpeedMult; // For dash rings
    f32 mSpeedMultTarget; // For dash rings
    s32 mSpeedMultAccelTime; // For dash rings
    s32 mSpeedMultTime; // For dash rings
    u32 mDamageDismount; // ALWAYS SET BEFORE USING!!
    s32 mGotoNearestPosWhenClipped; // Travel system
    /* 0x1CC */ bool mIsDive;
};
