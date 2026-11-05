#include "SurfRay.h"
#include "Util.h"

/*

?ｿｽG?ｿｽC's WaterInOutFx in ObjectInfluenceTable enables the air meter
NOTE: the encoding broke idk what string this was

*/

inline f32 min(f32 a, f32 b) {
    if (a >= b) {
        return b;
    }

    return a;
}

#ifdef INTELLISENSE_FIX
f32 __fabsf(f32);
#endif

extern "C" {
    void __kAutoMap_80050D60(const char* pSoundLabel, s32, s32); // Symbol for this is incorrect in Syati. Should be start ActionSoundPlayer or something like that
}

namespace NrvSurfRay {
    FULL_NERVE(SurfRayNrvWaitPlayer, SurfRay, WaitPlayer);
    FULL_NERVE(SurfRayNrvTurnToWait, SurfRay, TurnToWait);
    FULL_NERVE(SurfRayNrvWait, SurfRay, Wait);
    FULL_NERVE(SurfRayNrvRideAccel, SurfRay, RideAccel);
    FULL_NERVE(SurfRayNrvRideAccelTwist, SurfRay, RideAccelTwist);
    FULL_NERVE(SurfRayNrvRideFree, SurfRay, RideFree);
    FULL_NERVE(SurfRayNrvRideFreeTwist, SurfRay, RideFreeTwist);
    FULL_NERVE(SurfRayNrvRideJump, SurfRay, RideJump);
    FULL_NERVE(SurfRayNrvRideJumpHigh, SurfRay, RideJumpHigh);
    FULL_NERVE(SurfRayNrvRideFall, SurfRay, RideFall);
    FULL_NERVE(SurfRayNrvRideLand, SurfRay, RideLand);
    FULL_NERVE(SurfRayNrvTutorial, SurfRay, Tutorial);
    FULL_NERVE(SurfRayNrvWipeOut, SurfRay, WipeOut);
    FULL_NERVE(SurfRayNrvWipeIn, SurfRay, WipeIn);
    FULL_NERVE(SurfRayNrvReady, SurfRay, Ready);

    // New Nerves
    FULL_NERVE(SurfRayNrvPlayerExit, SurfRay, PlayerExit);
};

namespace {
    /*
    static const f32 sDistancePlayerNear = 1300.0f;
    // static const f32 sGravity
    // static const f32 sGroundReboundRate
    // static const f32 sWallReboundRate
    // static const f32 sReboundSpeedMin
    static const f32 sRunAccel = 0.5f;
    static const f32 sRunSpeedMax = 40.0f;
    // static const f32 sFlyUpSpeedMaxY
    // static const f32 sFallSpeedMaxY
    // static const f32 sRunGroundFrictionRate
    // static const f32 sRunAirFrictionRate
    static const f32 sSpeedToRumble = 5.0f;
    // static const f32 sWaterFriction
    // static const f32 sWaterGravity
    // static const f32 sWaterPressureRate
    // static const f32 sWaterWaveNrmAccelRate
    // static const f32 sWaterUpSideSpeedMax
    // static const f32 sWaterBottomReboundRate
    // static const f32 sWaterUpperPosOffset
    // static const f32 sWaterJudgeFront
    // static const f32 sWaterJudgeUp
    // static const f32 sWaterJudgeWidth
    // static const f32 sUpSideGroundFrictionRate
    // static const f32 sUpSideAirFrictionRate
    // static const f32 sUpSideSpeedMin
    static const s32 sStepEnableJumpAtAir = 15;
    static const s32 sStepToFallAtAir = 45;
    // static const f32 sJumpAccelMinY;
    // static const f32 sJumpAccelMaxY;
    static const f32 sJumpSpeedMaxY = 25.0f;
    static const f32 sJumpSpeedHigh = 23.0f;
    static const f32 sRunSpeedMinToRotate = 3.0f;
    // static const f32 sRotateAccelRate
    // static const f32 sPadAccelAddRateZ
    // static const f32 sPadAccelClamp
    // static const f32 sPadAccelInvalidMaxZ
    // static const f32 sPadAccelInvalidMinX
    // static const f32 sPadAccelInvalidFrictionRate
    // static const f32 sRotateSpeedFrictionRate
    // static const f32 sRotateFrictionRate
    // static const f32 sRotateSpeedMin
    // static const f32 sRotateSpeedMax
    static const f32 sRotateMaxZ = 70.0f;
    // static const f32 sRotateSpeedRate
    static const f32 sBlendRatioAxisUpAir = 0.02f;
    static const f32 sBlendRatioAxisUpGround = 0.1f;
    static const f32 sBlendRatioAxisFrontWall = 0.1f;
    static const f32 sPlayerPosOffsetY = 55.0f;
    static const f32 sPlayerPosOffsetZ = 12.0f;
    // static const f32 sRiderRotateInterpolateRate
    // static const f32 sRiderRotateRateScale
    static const f32 sTwistStartDiffMin = 0.2f;
    static const f32 sBtkSpeedMin = 1.0f;
    static const f32 sBtkSpeedMax = 4.0f;
    static const f32 sBtkSpeedRate = 0.4f;
    static const f32 sShadowAlphaMax = 64.0f;
    static const f32 sShadowAlphaSpeed = 10.0f;
    static const f32 sSpeedToEmitEffect = 6.0f;
    static const f32 sSpeedToEmitEffectFast = 20.0f;
    // static const f32 sMoveSeRotRate
    static const f32 sMoveSe0StartSpeed = 2.5f;
    static const f32 sMoveSe1StartSpeed = 7.5f;
    static const f32 sMoveSe2StartSpeed = 14.0f;
    static const f32 sMoveSe3StartSpeed = 25.0f;
    static const f32 sMoveSe3MaxSpeed = 35.0f;
    static const f32 sWindSeStartSpeed = 32.0f;
    static const f32 sWindSeMaxSpeed = 50.0f;
    // static const f32 sJumpInSoundMaxSpeed
    static const f32 sHitSoundStartVelocity = -10.0;
    // static const f32 sVelocityUpSideScale
    // static const f32 sRotateZFrictionRate
    // static const f32 sMarioAnimeBlendRate

    // New Const Parameters
    static const f32 sDiveAccel = 0.1f;
    static const f32 sDiveSpeedMax = 1.0f;
    */

    bool calcWaterShadowPos(TVec3f* pShadowPos, const TVec3f& rStartPos, const TVec3f& rShadowDir) {
        pShadowPos->set(rStartPos);
        TVec3f sample(rStartPos);

        for (s32 i = 0; i < 10; i++) {
            WaterInfo waterInfo = WaterInfo();

            if (MR::getWaterAreaObj(&waterInfo, sample)) {
                MR::getWaterAreaInfo(&waterInfo, sample, rShadowDir, false);
                pShadowPos->set(waterInfo.mSurfacePos);

                return true;
            }

            TVec3f step(rShadowDir);
            step.scale(100.0f);
            sample.add(step);
        }

        return false;
    }
};

#define WARP_POS_FORMAT "SurfRayWarpPos%d"

SurfRay::SurfRay(const char* pName, s32 channel)
    : LiveActor(pName), mSurfSpeed(0.0f), mOrthoSpeed(0.0f), mOrthoVelocity(0.0f, 0.0f, 0.0f), mSteerRate(0.0f), mSteerAccel(0.0f),
      mFront(0.0f, 0.0f, 1.0f), mUp(0.0f, 1.0f, 0.0f), mSide(1.0f, 0.0f, 0.0f), mBaseUp(0.0f, 1.0f, 0.0f), mBaseSide(1.0f, 0.0f, 0.0f),
      mGroundNormal(0.0f, 1.0f, 0.0f), mWarpPos(0.0f, 0.0f, 0.0f), mRider(nullptr), mPadChannel(channel), mRayTilt(0.0f), mInWater(false), mAirTime(0),
      mWaterNormal(0.0f, 1.0f, 0.0f), mTwistBufferSize(8), mWaterShadowPos(0.0f, 0.0f, 0.0f), mShadowAlpha(0.0f), mTwistBuffer(nullptr),
      mInTutorialArea(false), mInTutorial(false), mLectureIdx(0), mActorJointCtrl(nullptr), mProjmapFxMtxSetter(nullptr),
      mConst(nullptr), mDiveSpeed(0.0f) {
    mEffectHostMtx.identity();

    mSpeedMult = 0.0f;
    mSpeedMultTarget = 0.0f;
    mSpeedMultTime = 0;
    mSpeedMultAccelTime = 0;
    mGotoNearestPosWhenClipped = 0;
}

void SurfRay::init(const JMapInfoIter& rIter) {
    if (GameSequenceFunction::hasRetryGalaxySequence()) {
        //OSReport("generalpos\n");
        // MR::resetPosition(this, "スタート位置（サーフィン）");
    } else {
        //OSReport("defaultpos\n");
        // MR::initDefaultPos(this, rIter);
    }

    MR::initDefaultPos(this, rIter);
    resetAllInfo();
    MR::processInitFunction(this, rIter, false);

    mProjmapFxMtxSetter = MR::initDLMakerProjmapEffectMtxSetter(this);
    MR::newDifferedDLBuffer(this);
    mProjmapFxMtxSetter->updateMtxUseBaseMtx();

    MR::startBtk(this, "SurfRay");
    MR::startBtp(this, "Blink");

    MR::setEffectHostMtx(this, "Ripple", mEffectHostMtx);

    Color8 shadowColor(0, 40, 128, 64);
    MR::setShadowSurfaceOvalColor(this, nullptr, shadowColor);
    MR::setShadowSurfaceOvalAlpha(this, nullptr, 64);
    MR::setShadowProjectionPtr(this, nullptr, &mWaterShadowPos, &mWaterNormal);
    MR::setShadowSurfaceOvalAlpha(this, nullptr, (u8)mShadowAlpha & 0xFF);

    initNerve(&NrvSurfRay::SurfRayNrvWaitPlayer::sInstance, 0);

    MR::tryFindNamePos("ワープ位置（サーフィン）", &mWarpPos, nullptr);

    mConst = new SurfRayConst();
    s32 idx = -1;
    MR::getJMapInfoArg0NoInit(rIter, &idx);

    if (idx > -1) {
        mConst->initFromTable(idx);
    }
    else {
        mConst->initDefault();
    }

    mConst->mIsDiveEnabled = false;
    MR::getJMapInfoArg6NoInit(rIter, &mConst->mIsDiveEnabled);

    // TODO: Preferably have a way to hook this up to an in-game UI instead of hardcoding it
    //mConst->mIsStickControl = true;

    mActorJointCtrl = new ActorJointCtrl(this);
    mTwistBuffer = new f32[mTwistBufferSize];

    for (s32 count = 0; count < mTwistBufferSize; count++) {
        mTwistBuffer[count] = 0.0f;
    }

    MR::joinToGroupArray(this, rIter, 0, 32);

    // if (!GameSequenceFunction::hasRetryGalaxySequence()) {
    //     mInTutorialArea = true;
    // }

    MR::invalidateClipping(this);
    makeActorAppeared();

    MR::getJMapInfoArg7NoInit(rIter, &mGotoNearestPosWhenClipped);
    for (s32 i = 0; i < mGotoNearestPosWhenClipped; i++)
    {
        char buf[0x20];
        snprintf(buf, 0x20, WARP_POS_FORMAT, i);
        if (MR::tryRegisterNamePosLinkObj(this, rIter, buf))
            ;//OSReport("Linked %s\n", buf);
    }
}

void SurfRay::control() {
    // if (MR::testCorePadButtonPlus(0)) {
    //     receiveOtherMsg(ACTMES_TUTORIAL_OMIT, nullptr, nullptr);
    // }


    if (mRider)
        if (PSVECMag(mVelocity.toVecPtr()) > 10.0f || isUnderwater() || !tryInWater()) {
            if (MR::isValidSwitchA(this) && MR::isOnSwitchA(this))
                MR::offSwitchA(this);
        }
        else {
            if (MR::isValidSwitchA(this) && !MR::isOnSwitchA(this))
                MR::onSwitchA(this);
        }
    else if (MR::isValidSwitchA(this) && MR::isOnSwitchA(this))
        MR::offSwitchA(this);


    f32 surfspeed = mSurfSpeed;
    if (!mInWater && MR::isBindedGround(this))
    {
        //OSReport("Binded Out of water\n");
        surfspeed *= 0.92f;
    }

    mVelocity.set(mFront);
    mVelocity.scale(surfspeed);
    mVelocity.add(mOrthoVelocity);
    f32 rate = min(mSurfSpeed * mConst->mBtkSpeedRate + mConst->mBtkSpeedMin, mConst->mBtkSpeedMax);
    MR::setBtkRate(this, rate);
    mActorJointCtrl->update();
}

void SurfRay::calcAndSetBaseMtx() {
    PSVECCrossProduct(mBaseUp.toVecPtr(), mFront.toVecPtr(), mBaseSide.toVecPtr());
    MR::normalize(&mBaseSide);
    PSVECCrossProduct(mFront.toVecPtr(), mBaseSide.toVecPtr(), mBaseUp.toVecPtr());
    MR::normalize(&mBaseUp);
    mUp.set(mBaseUp);
    MR::rotateVecDegree(&mUp, mFront, mRotation.z);
    PSVECCrossProduct(mUp.toVecPtr(), mFront.toVecPtr(), mSide.toVecPtr());
    MR::normalize(&mSide);
    PSVECCrossProduct(mFront.toVecPtr(), mSide.toVecPtr(), mUp.toVecPtr());
    MR::normalize(&mUp);

    TPos3f mtx;
    mtx.identity();
    mtx[0][0] = mSide.x;
    mtx[1][0] = mSide.y;
    mtx[2][0] = mSide.z;
    mtx[0][1] = mUp.x;
    mtx[1][1] = mUp.y;
    mtx[2][1] = mUp.z;
    mtx[0][2] = mFront.x;
    mtx[1][2] = mFront.y;
    mtx[2][2] = mFront.z;
    mtx[0][3] = mTranslation.x;
    mtx[1][3] = mTranslation.y;
    mtx[2][3] = mTranslation.z;

    MR::setBaseTRMtx(this, mtx);
    mActorJointCtrl->setCallBackFunction();
    mProjmapFxMtxSetter->updateMtxUseBaseMtx();
}

void SurfRay::attackSensor(HitSensor* pSender, HitSensor* pReceiver) {
    if (!MR::tryGetItem(pSender, pReceiver)) {
        if (mSurfSpeed >= mConst->mAttackSpeedMax && MR::sendArbitraryMsg(ACTMES_PLAYER_PUNCH, pReceiver, pSender)) {
            return;
        }

        if (!(MR::isSensorPlayer(pReceiver) && canBind())) {
            MR::sendMsgPush(pReceiver, pSender);
        }
    }
}

bool SurfRay::receiveMsgEnemyAttack(u32 msg, HitSensor *pSender, HitSensor *pReceiver) {
    if (mSurfSpeed < mConst->mAttackSpeedMax) {
        mDamageDismount = msg;
        setNerve(&NrvSurfRay::SurfRayNrvPlayerExit::sInstance);
        return true;
    }

    return false;
}

bool SurfRay::receiveOtherMsg(u32 msg, HitSensor* pSender, HitSensor* pReceiver) {
    // OSReport("receiveOtherMsg { msg: %X; isBind: %d }\n", msg, MR::isEqualSensor(pReceiver, this, "Bind"));

    if (MR::isMsgAutoRushBegin(msg)) {
        if (!canBind()) { // || MR::getPlayerVelocity()->y > 0.0f
            return false;
        }

        mRider = MR::getSensorHost(pSender);
        // TODO-NONANIM MR::startStarPointerMode1PInvalid2PValid(this);
        MR::invalidateClipping(this);
        mRayTilt = 0.0f;


        Mario* pMario = MR::getMarioHolder()->getMarioActor()->mMario;
        pMario->closeStatus(nullptr); // Cancel Mario's status so that dismounting doesn't break...
        MR::startBckNoInterpole(this, "Wait");
        MR::startBckPlayerJ("サーフィン");
        MR::calcAnimDirect(this);

        DynamicJointCtrlKeeper *pJointCtrlKeeper = mActorJointCtrl->mDynamicJointCtrl;

        for (s32 i = 0; i < pJointCtrlKeeper->_4; i++) {
            DynamicJointCtrl *pCtrl = pJointCtrlKeeper->mControls[i];

            for (s32 i = 0; i < pCtrl->_8 - 1; i++) {
                pCtrl->mCtrlNodes[i]->reset();
            }

            pCtrl->mCtrlNodes[pCtrl->_8 - 1]->update(pCtrl->mActor, pCtrl->mCtrlNodes[pCtrl->_8 - 2]);
        }

        mInTutorial = false;
        // if (mInTutorial) {
        //     setNerve(&NrvSurfRay::SurfRayNrvTutorial::sInstance);
        // } else {
        //     setNerve(&NrvSurfRay::SurfRayNrvReady::sInstance);
        // }

        setNerve(&NrvSurfRay::SurfRayNrvRideFree::sInstance);
        return true;
    }

    if (MR::isMsgUpdateBaseMtx(msg)) {
        updateRiderMtx();
        return true;
    }

    if (MR::isMsgRushCancel(msg)) {
        mRider = nullptr;
        mSurfSpeed = 0.0f;
        if (tryWarpToRespawn(0.0f, false)) {
            mVelocity.zero();
            mOrthoSpeed = 0;
            mOrthoVelocity.zero();
        }
        setNerve(&NrvSurfRay::SurfRayNrvWait::sInstance);
        return true;
    }

    if (msg == ACTMES_PASS_RING)
    {
        if (MR::isEqualString(pSender->mActor->mName, "水中ダッシュリング"))
        {
            DashRing* pRing = (DashRing*)pSender->mActor;
            //OSReport("Passed DashRing: %ff\n", pRing->mBoostSpeed);
            mSpeedMultTarget = pRing->mBoostSpeed;
            mSpeedMultTime = pRing->mBoostTime + pRing->mAccelTime;
            mSpeedMultAccelTime = pRing->mAccelTime;
        }
    }

    /*
    if (msg = ACTMES_TUTORIAL_START) {
        MR::setPlayerPos(mTranslation);
        mInTutorial = true;
        return true;
    }

    if (msg == ACTMES_TUTORIAL_NEXT) {
        mLectureIdx++;
        setNerve(&NrvSurfRay::SurfRayNrvTutorial::sInstance);
        return true;
    }

    if (msg == ACTMES_TUTORIAL_PREV) {
        mLectureIdx--;
        setNerve(&NrvSurfRay::SurfRayNrvTutorial::sInstance);
        return true;
    }

    if (msg == ACTMES_TUTORIAL_PASS) {
        mInTutorial = false;
        setNerve(&NrvSurfRay::SurfRayNrvRideFree::sInstance);
        return true;
    }

    if (msg == ACTMES_TUTORIAL_OMIT) {
        mInTutorialArea = false;
        // TODO-NONANIM MR::resetPosition(this, "スタート位置（サーフィン）");
        resetAllInfo();
        MR::setPlayerPos(mTranslation);
        // TODO-ANIM MR::startBckPlayer("SurfRide", 0);
        MR::resetCameraMan();
        return true;
    }

    if (MR::isMsgRaceReady(msg)) {
        setNerve(&NrvSurfRay::SurfRayNrvReady::sInstance);
        return true;
    }

    if (MR::isMsgRaceStart(msg)) {
        setNerve(&NrvSurfRay::SurfRayNrvRideFree::sInstance);
        return true;
    }

    if (MR::isMsgRaceReset(msg)) {
        MR::endBindAndPlayerWait(this);
        resetAllInfo();
        setNerve(&NrvSurfRay::SurfRayNrvWait::sInstance);
        MR::endStarPointerMode(this);
        kill();
        return true;
    }
    */

    return false;
}

void SurfRay::exeWaitPlayer() {
    if (MR::isFirstStep(this)) {
        MR::startBck(this, "FirstWait", nullptr);
    }

    calcWaterShadowPos(&mWaterShadowPos, mTranslation, mGravity);

    if (MR::isNearPlayer(this, mConst->mDistancePlayerNear)) {
        setNerve(&NrvSurfRay::SurfRayNrvTurnToWait::sInstance);
    }
}

void SurfRay::exeTurnToWait() {
    if (MR::isFirstStep(this)) {
        MR::startBck(this, "FirstWaitTurn", nullptr);
        MR::startSound(this, "SE_SM_SURF_RAY_TURNTO_MR", -1, -1);
    }

    if (MR::isBckStopped(this)) {
        setNerve(&NrvSurfRay::SurfRayNrvWait::sInstance);
    }
}

void SurfRay::exeWait() {
    if (MR::isFirstStep(this)) {
        MR::startBck(this, "Wait", nullptr);
    }

    mOrthoVelocity.zero();

    tryWarpToRespawn();
}

void SurfRay::exeRideAccel() {
    if (MR::isFirstStep(this)) {
        MR::startBckPlayerJ("サーフィン（加速）");
        MR::startBck(this, "RunDash", nullptr);
    }

    if (!updateRideAccel() && isTwistStart()) {
        setNerve(&NrvSurfRay::SurfRayNrvRideAccelTwist::sInstance);
    }
}

void SurfRay::exeRideAccelTwist() {
    if (MR::isFirstStep(this)) {
        MR::startBckPlayerJ("サーフィン傾き開始（加速）");
    }

    if (!updateRideAccel() && MR::isBckStoppedPlayer()) {
        setNerve(&NrvSurfRay::SurfRayNrvRideAccel::sInstance);
    }
}

void SurfRay::exeRideFree() {
    if (MR::isFirstStep(this)) {
        MR::startBck(this, "Run", nullptr);
        MR::startBckPlayerJ("サーフィン");
    }

    if (tryDismount())
        return;

    if (!updateRideFree() && isTwistStart()) {
        setNerve(&NrvSurfRay::SurfRayNrvRideFreeTwist::sInstance);
    }
}

void SurfRay::exeRideFreeTwist() {
    if (MR::isFirstStep(this)) {
        MR::startBckPlayerJ("サーフィン傾き開始");
    }

    if (tryDismount())
        return;

    if (!updateRideFree() && MR::isBckStoppedPlayer()) {
        setNerve(&NrvSurfRay::SurfRayNrvRideFree::sInstance);
    }
}

void SurfRay::exeRideJump() {
    if (MR::isFirstStep(this)) {
        /* TODO-ANIM-SINGLE-TABLE */MR::startBckPlayerJ("サーフィンジャンプ");
        MR::startBck(this, "Jump", nullptr);
        MR::startSound(mRider, "SE_PV_JUMP_S", -1, -1);
    }

    if (!updateRide() && mVelocity.dot(mGravity) > 0.0f) {
        setNerve(&NrvSurfRay::SurfRayNrvRideFall::sInstance);
    }
}

void SurfRay::exeRideJumpHigh() {
    if (MR::isFirstStep(this)) {
        /* TODO-ANIM-SINGLE-TABLE */MR::startBckPlayerJ("サーフィンハイジャンプ");
        MR::startBck(this, "Jump", nullptr);
        MR::startSound(mRider, "SE_PV_JUMP_JOY", -1, -1);
    }

    if (!updateRide() && mVelocity.dot(mGravity) > 0.0f) {
        setNerve(&NrvSurfRay::SurfRayNrvRideFall::sInstance);
    }
}

void SurfRay::exeRideFall() {
    if (MR::isFirstStep(this)) {
        MR::startBckPlayerJ("サーフィン落下");
        MR::startBck(this, "Fall", nullptr);
    }

    if (!updateRide() && mVelocity.dot(mGravity) > 0.0f && mInWater) {
        setNerve(&NrvSurfRay::SurfRayNrvRideLand::sInstance);
        MR::startSound(this, "SE_SM_SURF_RAY_LANDW", -1, -1);
    }
}

void SurfRay::exeRideLand() {
    if (MR::isFirstStep(this)) {
        /* TODO-ANIM-SINGLE-TABLE */MR::startBckPlayerJ("サーフィン着地");
        MR::startBck(this, "Land", nullptr);
    }

    if (!updateRide() && !tryJumpOrFall() && MR::isBckStopped(this)) {
        setNerve(&NrvSurfRay::SurfRayNrvRideFree::sInstance);
    }
}

void SurfRay::exeTutorial() {
    TVec3f v1(mFront);
    updateRide();
    mOrthoVelocity.scale(0.5f);
    mFront.set(v1);

    mSurfSpeed = 0.0f;
    mRotation.z *= 0.85f;

    f32 rot; // having this here fixes a compiler warning
    switch (mLectureIdx) {
    case 0:
        if (MR::isFirstStep(this)) {
            MR::startBckPlayerJ("サーフィン着地");
            MR::startBck(this, "Land", nullptr);
        }

        if (MR::isBckOneTimeAndStoppedPlayer()) {
            MR::startBckPlayer("SurfLectureUnbalance", nullptr);
        }

        if (MR::isBckOneTimeAndStopped(this)) {
            MR::startBck(this, "LectureUnbalance", nullptr);
        }
        break;
    case 2:
        if (MR::isFirstStep(this)) {
            MR::startBckPlayer("SurfLectureUnbalance", nullptr);
            MR::startBck(this, "LectureUnbalance", nullptr);
        }
        break;
    case 3:
        if (MR::isFirstStep(this)) {
            MR::startBckPlayer("SurfRide", nullptr);
            MR::startBck(this, "Wait", nullptr);
        }
        break;
    case 4:
    case 8:
    case 12:
        if (MR::isFirstStep(this)) {
            MR::startBckPlayer("SurfLectureAnswer", nullptr);
            MR::startBck(this, "LectureAnswer", nullptr);
            MR::startSound(this, "SE_SM_SURF_RAY_JUMPOUT1", -1, -1);
        }

        if (MR::isBckOneTimeAndStoppedPlayer()) {
            MR::startBckPlayerJ("サーフィン");
        }

        if (MR::isBckOneTimeAndStopped(this)) {
            MR::startBck(this, "Wait", nullptr);
        }
        break;
    case 5:
    case 6:
    case 9:
    case 10:
        if (MR::isFirstStep(this)) {
            MR::startBckPlayerJ("サーフィン");
            MR::startBck(this, "Wait", nullptr);
        }
        break;
    case 7:
    case 11:
        if (MR::isFirstStep(this)) {
            MR::startBckPlayerJ("サーフィン傾き開始");
        }

        rot = __fabsf((mRotation.z / mConst->mRotateMaxZ) * 0.6f);

        if (mRotation.z < 0.0f) {
            MR::setBckBlendWeight(1.0f - rot, rot, 0.0f);
        } else {
            MR::setBckBlendWeight(1.0f - rot, 0.0f, rot);
        }
        break;
    case 13:
        break;
    default:
        break;
    }
}

void SurfRay::exeWipeOut() {
    if (MR::isFirstStep(this)) {
        MR::closeWipeCircle(-1);
    }

    if (!updateRide() && !MR::isWipeActive()) {
        // TODO-NONANIM MR::resetPosition(this, "スタート位置（サーフィン）");
        resetAllInfo();
        MR::startBckPlayerJ("サーフィン傾き開始");
        MR::resetCameraMan();
        setNerve(&NrvSurfRay::SurfRayNrvWipeIn::sInstance);
    }
}

void SurfRay::exeWipeIn() {
    if (MR::isFirstStep(this)) {
        MR::openWipeCircle(-1);
    }

    if (!MR::isWipeActive()) {
        setNerve(&NrvSurfRay::SurfRayNrvRideFree::sInstance);
    }
}

void SurfRay::exeReady() {
    if (MR::isFirstStep(this)) {
        MR::endStartPosCamera();
        MR::startBck(this, "WaitRaceStart", nullptr);
        MR::startBckPlayerJ("サーフィン傾き開始");
        MR::tryEmitEffect(this, "Ripple");
        MR::tryDeleteEffect(this, "RunDashSplash");
        MR::tryDeleteEffect(this, "SwimSplash");
    }

    MR::calcGravity(this);
    updateToWater();
    updateInfo();
    updateToMap();
    updateSound();
    updateRiderMtx();
    mOrthoVelocity.scale(0.5f);
    mSurfSpeed = 0.0f;
    mRotation.z = 0.0f;
}

void SurfRay::resetAllInfo() {
    TRot3f rotMtx;
    rotMtx.identity();
    MR::makeMtxRotate(rotMtx, mRotation);

    rotMtx.getXDir(mSide);
    rotMtx.getYDir(mUp);
    rotMtx.getZDir(mFront);

    mBaseUp.set(mUp);
    mBaseSide.set(mSide);

    mRotation.zero();
    mVelocity.zero();
    mOrthoVelocity.zero();

    mInWater = false;
    mSurfSpeed = 0.0f;
    mOrthoSpeed = 0.0f;
    mSteerRate = 0.0f;
    mSteerAccel = 0.0f;
    mAirTime = 0;

    mDiveSpeed = 0.0f;
    mIsDive = false;

    MR::tryDeleteEffect(this, "SwimSplash");
    MR::tryDeleteEffect(this, "RunDashSplash");
    MR::tryDeleteEffect(this, "Ripple");
}

bool SurfRay::updateRideAccel() {
    if (updateRide()) {
        return true;
    }

    if (tryJumpOrFall()) {
        return true;
    }

    if (!MR::testCorePadButtonA(mPadChannel)) {
        setNerve(&NrvSurfRay::SurfRayNrvRideFree::sInstance);
        return true;
    }

    return false;
}

bool SurfRay::updateRideFree() {
    if (updateRide()) {
        return true;
    }

    if (tryJumpOrFall()) {
        return true;
    }

    if (MR::testCorePadButtonA(mPadChannel)) {
        setNerve(&NrvSurfRay::SurfRayNrvRideAccel::sInstance);
        return true;
    }

    return false;
}

bool SurfRay::updateRide() {
    if (mInTutorialArea && mTranslation.z > mWarpPos.z) {
        mInTutorialArea = false;
        setNerve(&NrvSurfRay::SurfRayNrvWipeOut::sInstance);
        return true;
    }

    MR::calcGravity(this);
    updateToWater();
    updateInfo();
    updateToMap();
    updateAccel();
    updateDive();
    updateBoost();
    updateEffect();
    updateSound();
    updateRotate();

    return false;
}

void SurfRay::updateInfo() {
    if (MR::isBindedGround(this)) {
        f32 sfxLvl = MR::getLinerValueFromMinMax(mSurfSpeed, 0.0f, mConst->mRunSpeedMax, 100.0f, 1000.0f);

        MR::startLevelSound(this, "SE_SM_LV_SURF_RAY_LAND", sfxLvl, -1, -1);

        if (MR::reboundVelocityFromCollision(this, 0.3f, 10.0f, 1.0f) && PSVECMag(mVelocity.toVecPtr()) > mConst->mSpeedToRumble) {
            MR::tryRumblePadMiddle(this, mPadChannel);
        }
    }

    if (MR::isBindedWall(this)) {
        if (mVelocity.dot(MR::getWallNormal(this)) < mConst->mHitSoundStartVelocity) {
            MR::startSound(this, "SE_SM_SURF_RAY_HIT_WALL", -1, -1);
        }

        if (MR::reboundVelocityFromCollision(this, 0.8f, 10.0f, 1.0f) && PSVECMag(mVelocity.toVecPtr()) > mConst->mSpeedToRumble) {
            MR::tryRumblePadMiddle(this, mPadChannel);
        }
    }

    mSurfSpeed = mFront.dot(mVelocity);
    TVec3f proj(mFront);
    proj.scale(mSurfSpeed);
    mOrthoVelocity.set(mVelocity);
    mOrthoVelocity.sub(proj);
    mOrthoSpeed = PSVECMag(mOrthoVelocity.toVecPtr());
}

void SurfRay::updateToMap() {
    TVec3f v1(mGravity);

    if (mInWater) {
        v1.scale(0.1f);
    } else {
        v1.scale(0.8f);
    }

    mOrthoVelocity.add(v1);

    if (MR::isBinded(this)) {
        if (MR::isBindedGround(this)) {
            mGroundNormal.set(MR::getBindedNormal(this));
            MR::vecBlendSphere(&mBaseUp, mBaseUp, mGroundNormal, mConst->mBlendRatioAxisUpGround);
        }

        if (MR::isBindedWall(this)) {
            TVec3f v2(mVelocity);
            MR::normalize(&v2);
            MR::turnVecToPlane(&v2, v2, MR::getWallNormal(this));
            MR::turnVecToPlane(&v2, v2, mGravity);
            TVec3f v3;
            MR::vecBlend(&v3, mFront, v2, mConst->mBlendRatioAxisFrontWall);
            PSVECCrossProduct(mBaseUp.toVecPtr(), v3.toVecPtr(), mBaseSide.toVecPtr());
        }
    } else if (mInWater) {
        MR::vecBlendSphere(&mBaseUp, mBaseUp, mWaterNormal, mConst->mBlendRatioAxisUpGround);
    } else {
        TVec3f v4(mGravity);
        v4.scale(-1.0f);
        MR::vecBlendSphere(&mBaseUp, mBaseUp, v4, mConst->mBlendRatioAxisUpAir);
    }

    PSVECCrossProduct(mBaseSide.toVecPtr(), mBaseUp.toVecPtr(), mFront.toVecPtr());
    MR::normalize(&mFront);
}

void SurfRay::updateToWater() {
    if (tryInWater()) {
        if (!mInWater) {
            f32 lvl = MR::getLinerValueFromMinMax(PSVECMag(mOrthoVelocity.toVecPtr()), 0.0f, 20.0f, 100.0f, 1000.0f);

            if (mAirTime > 30) {
                MR::tryRumblePadMiddle(this, mPadChannel);
            }

            if (mAirTime > 80 && PSVECMag(mOrthoVelocity.toVecPtr()) > 20.0f) {
                MR::startSound(this, "SE_SM_SURF_RAY_JUMPIN2", -1, -1);
            } else if (mAirTime > 5 && PSVECMag(mOrthoVelocity.toVecPtr()) > 10.0f) {
                MR::startSound(this, "SE_SM_SURF_RAY_JUMPIN1", lvl, -1);
            } else {
                MR::startSound(this, "SE_SM_SURF_RAY_JUMPIN0", lvl, -1);
            }
        }

        mInWater = true;
        mAirTime = 0;

        if (PSVECMag(mVelocity.toVecPtr()) > mConst->mSpeedToRumble) {
            MR::tryRumblePadWeak(this, mPadChannel);
        }

        MR::getWaterAreaInfo(&mWaterInfo, mTranslation, mGravity, false);
        mWaterPosition.set(mWaterInfo.mSurfacePos);
        mWaterNormal.set(mWaterInfo.mSurfaceNormal);
        f32 innerProd = mGravity.dot(mVelocity);

        if (!mIsDive) {
            if (innerProd > 0.0f && mWaterInfo._4 < innerProd) {
                TVec3f v2(mGravity);
                v2.scale(innerProd);
                v2.scale(1.5f);
                mVelocity.sub(v2);
            } else {
                f32 camWaterDepth = mWaterInfo.mCameraWaterDepth;
                f32 waveHeight = mWaterInfo.mWaveHeight;
                f32 f0 = camWaterDepth + waveHeight;
                mVelocity.sub(mGravity * f0 * 0.01f);
            }
        }

        
    }
    else {
        if (mInWater) {
            f32 lvl = MR::getLinerValueFromMinMax(mSurfSpeed, 0.0f, 30.0f, 200.0f, 1000.0f);
            MR::startSound(this, "SE_SM_SURF_RAY_JUMPOUT1", lvl, -1);
            mInWater = false;
        }

        mAirTime++;
    }


    WaterInfo waterInfo;
    TVec3f v(mTranslation + mGravity * 20.0f);

    if (MR::getWaterAreaObj(&waterInfo, v)) {
        mShadowAlpha -= mConst->mShadowAlphaSpeed;
    } else if (calcWaterShadowPos(&mWaterShadowPos, mTranslation, mGravity)) {
        mShadowAlpha += mConst->mShadowAlphaSpeed;
    } else {
        mShadowAlpha -= mConst->mShadowAlphaSpeed;
    }

    mShadowAlpha = MR::clamp(mShadowAlpha, 0.0f, mConst->mShadowAlphaMax);
    MR::setShadowSurfaceOvalAlpha(this, 0, (u8)mShadowAlpha & 0xff);
}

void SurfRay::updateAccel() {
    if (MR::testCorePadButtonA(mPadChannel)) {
        mSurfSpeed += mConst->mRunAccel;
    } else {
        mSurfSpeed *= 0.99f;
    }

    mSurfSpeed = MR::clamp(mSurfSpeed, 0.0f, mConst->mRunSpeedMax + (mConst->mRunSpeedMax * mSpeedMult));


    if (!mWaterInfo.isInWater()) {
        MR::tryDeleteEffect(this, "SwimSplash");
        MR::tryDeleteEffect(this, "RunDashSplash");
        MR::tryDeleteEffect(this, "Ripple");
    }
    else if (mSurfSpeed > mConst->mSpeedToEmitEffectFast) {
        MR::tryEmitEffect(this, "RunDashSplash");
        MR::tryDeleteEffect(this, "SwimSplash");
        MR::tryDeleteEffect(this, "Ripple");
    }
    else if (mSurfSpeed > mConst->mSpeedToEmitEffect) {
        MR::tryEmitEffect(this, "SwimSplash");
        MR::tryDeleteEffect(this, "RunDashSplash");
        MR::tryDeleteEffect(this, "Ripple");
    }
    else {
        MR::tryEmitEffect(this, "Ripple");
        MR::tryDeleteEffect(this, "RunDashSplash");
        MR::tryDeleteEffect(this, "SwimSplash");
        MR::makeMtxUpFrontPos(&mEffectHostMtx, -mGravity, mFront, mWaterInfo.mSurfacePos);
    }


    if (MR::isBinded(this)) {
        mOrthoVelocity.scale(0.9f);
    }
    else {
        mOrthoVelocity.scale(0.995f);
    }

    if (MR::isNearZero(mOrthoVelocity, 0.1f)) {
        mOrthoVelocity.zero();
    }

    if (mWaterInfo.isInWater() && !isNerve(&NrvSurfRay::SurfRayNrvRideJump::sInstance)) {
        mOrthoVelocity.scale(0.95f);
    }
}

void SurfRay::updateRotate() {
    f32 steerAccel;
    f32 accelX = 0.0f;

    if (isRotateStart()) {
        TVec3f accel(0.0f, 0.0f, 0.0f);
        calcRotateAccel(&accel);

        if (accel.z > -0.7f || __fabsf(accel.x) > 0.15f) {
            f32 twistAngle = accel.x;
            f32 accelZ = MR::clamp(-accel.z, 0.0f, 1.0f);

            if (twistAngle > 0.0f) {
                twistAngle += accelZ;
            } else if (twistAngle < 0.0f) {
                twistAngle -= accelZ;
            }

            steerAccel = MR::clamp(twistAngle, -1.5f, 1.5f);
            accelX = accel.x;

            if (accelX < 0.0f) {
                f32 tiltClamp = MR::clamp(accelX, -1.0f, 0.0f);
                mRayTilt = MR::getInterpolateValue(0.3f, mRayTilt, tiltClamp);
            } else if (accelX > 0.0f) {
                f32 tiltClamp = MR::clamp(accelX, 0.0f, 1.0f);
                mRayTilt = MR::getInterpolateValue(0.3f, mRayTilt, tiltClamp);
            }
        } else {
            mRayTilt = MR::getInterpolateValue(0.3f, mRayTilt, 0.0f);
            steerAccel = mSteerAccel * 0.95f;
        }

        mSteerAccel = steerAccel;
        mSteerRate += steerAccel;
        mSteerRate = MR::clamp(mSteerRate, -30.0f, 30.0f);
    } else {
        mRayTilt = MR::getInterpolateValue(0.3f, mRayTilt, 0.0f);
        mSteerAccel = 0.0f;
    }

    mSteerRate *= 0.95f;
    f32 abs = __fabsf(mSteerRate);

    if (abs < 0.1f) {
        mSteerRate = 0.0f;
    }

    mRotation.z *= 0.7f;
    mRotation.z += mSteerRate;
    mRotation.z = MR::clamp(mRotation.z, -mConst->mRotateMaxZ, mConst->mRotateMaxZ); // TODO-NONANIM make a min rot

    f32 rayTilt = MR::clamp(mRayTilt * 1.2f, -1.0f, 1.0f);

    if (rayTilt > 0.0f) {
        MR::setBckBlendWeight(1.0f - rayTilt, 0.0f, rayTilt);
    } else {
        MR::setBckBlendWeight(rayTilt + 1.0f, -rayTilt, 0.0f);
    }

    TRot3f mtx;
    mtx.identity();
    mtx.setRotate(mBaseUp, -mRotation.z * 0.00028f);
    mtx.mult(mFront, mFront);

    for (s32 i = mTwistBufferSize - 1; i >= 1; i--) {
        mTwistBuffer[i] = mTwistBuffer[i - 1];
    }

    mTwistBuffer[0] = accelX;
}

void SurfRay::updateSound() {
    f32 lvl;

    if (mSurfSpeed > mConst->mMoveSe0StartSpeed && mSurfSpeed < mConst->mMoveSe3StartSpeed) {
        if (mSurfSpeed < mConst->mMoveSe2StartSpeed) {
            lvl = MR::getLinerValueFromMinMax(mSurfSpeed, mConst->mMoveSe0StartSpeed, mConst->mMoveSe1StartSpeed, 0.1f, 1.0f);
        } else {
            lvl = MR::getLinerValueFromMinMax(mSurfSpeed, mConst->mMoveSe2StartSpeed, mConst->mMoveSe3StartSpeed, 1.0f, 0.0f);
        }

        MR::startLevelSound(this, "SE_SM_LV_SURF_RAY_MOVE0", lvl * 1000.0f, -1, -1);
    }

    if (mInWater) {
        if (mSurfSpeed > mConst->mMoveSe1StartSpeed) {
            lvl = MR::getLinerValueFromMinMax(mSurfSpeed, mConst->mMoveSe1StartSpeed, mConst->mMoveSe2StartSpeed, 0.1f, 1.0f);

            MR::startLevelSound(this, "SE_SM_LV_SURF_RAY_MOVE1", lvl * 1000.0f, -1, -1);
        }
    }

    if (mInWater) {
        if (mSurfSpeed > mConst->mMoveSe2StartSpeed) {
            lvl = MR::getLinerValueFromMinMax(mSurfSpeed, mConst->mMoveSe2StartSpeed, mConst->mMoveSe3StartSpeed, 0.1f, 1.0f);

            MR::startLevelSound(this, "SE_SM_LV_SURF_RAY_MOVE2", lvl * 1000.0f, -1, -1);
        }
    }

    if (mSurfSpeed > mConst->mMoveSe3StartSpeed) {
        lvl = MR::getLinerValueFromMinMax(mSurfSpeed, mConst->mMoveSe3StartSpeed, mConst->mMoveSe3MaxSpeed, 0.1f, 1.0f);

        if (mInWater) {
            MR::startLevelSound(this, "SE_SM_LV_SURF_RAY_MOVE3", lvl * 1000.0f, -1, -1);
        }
    }

    if (PSVECMag(mVelocity.toVecPtr()) > mConst->mWindSeStartSpeed) {
        lvl = MR::getLinerValueFromMinMax(PSVECMag(mVelocity.toVecPtr()), mConst->mWindSeStartSpeed, mConst->mWindSeMaxSpeed, 0.1f, 1.0f);

        MR::startLevelSound(this, "SE_SM_SURF_RAY_MOVE_WIND", lvl * 1000.0f, -1, -1);
    }

    f32 rotateRate = __fabsf(mRotation.z) / mConst->mRotateMaxZ;

    if (mInWater && rotateRate > 0.45f) {
        lvl = MR::getLinerValueFromMinMax(mSurfSpeed, 0.0f, 25.0f, 100.0f, 1000.0f);

        MR::startLevelSound(this, "SE_SM_LV_SURF_RAY_CURVE", lvl, -1, -1);
    }
}

void SurfRay::updateRiderMtx() {
    MtxPtr mtx1 = MR::getJointMtx(this, "Center");
    TPos3f mtx;
    mtx.setInline(mtx1);

    mtx[0][3] += mtx1[0][1] * mConst->mPlayerPosOffsetY + mtx1[0][2] * mConst->mPlayerPosOffsetZ;
    mtx[1][3] += mtx1[1][1] * mConst->mPlayerPosOffsetY + mtx1[1][2] * mConst->mPlayerPosOffsetZ;
    mtx[2][3] += mtx1[2][1] * mConst->mPlayerPosOffsetY + mtx1[2][2] * mConst->mPlayerPosOffsetZ;

    MR::setBaseTRMtx(mRider, mtx);
}

bool SurfRay::tryInWater() {
    if (MR::getWaterAreaObj(&mWaterInfo, mTranslation)) {
        return true;
    }

    TVec3f v1(mFront * 100.0f + mTranslation);
    if (MR::getWaterAreaObj(&mWaterInfo, v1)) {
        return true;
    }

    TVec3f v2(mUp * 150.0f + mTranslation);
    if (MR::getWaterAreaObj(&mWaterInfo, v2)) {
        return true;
    }

    TVec3f v3(mFront);
    MR::rotateVecDegree(&v3, -mGravity, -90.0f);
    TVec3f v3a(v3 * 150.0f + mTranslation);
    if (MR::getWaterAreaObj(&mWaterInfo, v3a)) {
        return true;
    }

    TVec3f v4(mFront);
    MR::rotateVecDegree(&v4, -mGravity, 90.0f);
    TVec3f v4a(v4 * 150.0f + mTranslation);
    if (MR::getWaterAreaObj(&mWaterInfo, v4a)) {
        return true;
    }

    TVec3f v5(mSide * 150.0f + mTranslation);
    if (MR::getWaterAreaObj(&mWaterInfo, v5)) {
        return true;
    }

    TVec3f v6((-mSide) * 150.0f + mTranslation);
    if (MR::getWaterAreaObj(&mWaterInfo, v6)) {
        return true;
    }

    return false;
}

bool SurfRay::tryJumpOrFall() {
    if (!isUnderwater() && MR::isPadSwing(mPadChannel) && (MR::isBinded(this) || mWaterInfo.isInWater() || mAirTime < mConst->mStepEnableJumpAtAir)) {
        f32 f0 = (mSurfSpeed / mConst->mRunSpeedMax) * (((mConst->mRotateMaxZ - __fabsf(mRotation.z)) * 5.0f) / mConst->mRotateMaxZ) + 15.0f;
        TVec3f v1(mGroundNormal);

        if (mWaterInfo.isInWater()) {
            v1.set(mWaterInfo.mSurfaceNormal);
        }

        v1.scale(f0);

        if (mOrthoVelocity.dot(mGravity) > 0.0f) {
            MR::vecKillElement(mOrthoVelocity, mGravity, &mOrthoVelocity);
        }

        mOrthoVelocity.add(v1);

        if (PSVECMag(mOrthoVelocity.toVecPtr()) > mConst->mJumpSpeedMaxY) {
            MR::normalize(&mOrthoVelocity);
            mOrthoVelocity.scale(mConst->mJumpSpeedMaxY);
        }

        if (PSVECMag(mOrthoVelocity.toVecPtr()) > mConst->mJumpSpeedHigh) {
            setNerve(&NrvSurfRay::SurfRayNrvRideJumpHigh::sInstance);
        } else {
            setNerve(&NrvSurfRay::SurfRayNrvRideJump::sInstance);
        }

        return true;
    }

    if (mAirTime > mConst->mStepToFallAtAir) {
        setNerve(&NrvSurfRay::SurfRayNrvRideFall::sInstance);
        return true;
    }

    return false;
}

bool SurfRay::isTwistStart() const {
    f32 maxTwist = 0.0f;

    for (s32 i = 1; i < mTwistBufferSize; i++) {
        f32 twistDiff = __fabsf(mTwistBuffer[0] - mTwistBuffer[i]);

        if (twistDiff > maxTwist) {
            maxTwist = twistDiff;
        }
    }

    return maxTwist > mConst->mTwistStartDiffMin;
}

bool SurfRay::isRotateStart() const {
    if (mInTutorial) {
        if (mLectureIdx == 7 || mLectureIdx == 11) {
            return true;
        }

        return false;
    }

    return mSurfSpeed > mConst->mRunSpeedMinToRotate || MR::testCorePadButtonA(mPadChannel);
}


// Helps with diving
void SurfRay::updateBoost() {
    if (isNerve(&NrvSurfRay::SurfRayNrvPlayerExit::sInstance))
        mSpeedMultTarget = 0.0f;

    if (mSpeedMultTime < 0)
        return;
    mSpeedMultTime--;

    if (mSpeedMultAccelTime <= 0)
        mSpeedMultAccelTime = 1; // Prevent divide by Zero

    // Calculate boost step rate
    f32 distancetotargetmult = mSpeedMultTarget - mSpeedMult;
    f32 step = distancetotargetmult / (f32)(mSpeedMultAccelTime--);
    mSpeedMult += step;

    if (MR::isNearZero(mSpeedMultTarget - mSpeedMult, 0.001f))
        mSpeedMult = mSpeedMultTarget;

    if (mSpeedMultTime < 60 && mSpeedMultTarget != 0.0f) {
        // flag for reset speed
        mSpeedMultTarget = 0.0f;
        mSpeedMultAccelTime = mSpeedMultTime;
    }

    mOrthoVelocity.add(mFront * mSpeedMult);

    //OSReport("Boost: %ff / %ff   Accel/Time: %d / %d\n", mSpeedMult, mSpeedMultTarget, mSpeedMultAccelTime, mSpeedMultTime);
}

bool SurfRay::isUnderwater(f32 dist) {
    bool isUnderWater = false;
    if (tryInWater()) {
        isUnderWater = PSVECDistance(mWaterPosition, mTranslation) > dist;
    }
    return isUnderWater;
}

bool SurfRay::tryDismount() {

    if (MR::isPowerStarGetDemoActive())
        goto ForceDismount;

    if (MR::isPlayerConfrontDeath())
        goto ForceDismount;

    if (isUnderwater())
        return false; // Do not dismount underwater

    if (PSVECMag(mVelocity.toVecPtr()) > 12.0f)
        return false; // Do not dismount at high speeds

    if (!MR::testSubPadButtonZ(mPadChannel))
        return false; // Hold Z...

    if (!MR::testCorePadTriggerA(mPadChannel))
        return false; // ...and Press A!
    
ForceDismount:
    mDamageDismount = 0;
    setNerve(&NrvSurfRay::SurfRayNrvPlayerExit::sInstance);
    return true;
}

bool SurfRay::tryWarpToRespawn(f32 dist, bool needClipped) {
    if (mGotoNearestPosWhenClipped <= 0)
        return false;

    if (MR::calcDistanceToPlayer(mTranslation) < dist)
        return false;

    f32 bodyradius = MR::getSensorRadius(this, "Body");
    if (needClipped && !MR::isJudgedToClipFrustum(mTranslation, bodyradius))
        return false;

    //OSReport("Player too far. Attempting Teleport...\n");


    // find nearest warp point
    s32 BestIDX = -1;
    f32 BestDist = 1000000.0f; // should be large enough... I hope...
    for (s32 i = 0; i < mGotoNearestPosWhenClipped; i++)
    {
        char buf[0x20];
        snprintf(buf, 0x20, WARP_POS_FORMAT, i);
        TVec3f translation;
        TVec3f rotation;
        if (!MR::tryFindLinkNamePos(this, buf, &translation, &rotation))
            continue; // pos not found

        f32 distancetopoint = MR::calcDistanceToPlayer(translation);

        if (distancetopoint < dist) // if too close to player, we have to check for clipping
            if (needClipped && !MR::isJudgedToClipFrustum(translation, bodyradius))
                continue; // pos not clipped

        //OSReport("Distance to %s: %ff\n", buf, distancetopoint);

        if (BestDist < distancetopoint)
            continue;

        // Set best
        BestIDX = i;
        BestDist = distancetopoint;
    }

    //OSReport("Best ID = %d\n", BestIDX);
    if (BestIDX < 0)
        return false;

    char destposname[0x20];
    snprintf(destposname, 0x20, WARP_POS_FORMAT, BestIDX);
    //OSReport("Trying to teleport to %s\n", destposname);
    if (!MR::tryFindLinkNamePos(this, destposname, &mTranslation, &mRotation))
    {
        //OSReport("Failed to find %s\n", destposname);
        return false;
    }

    //OSReport("Teleported to %s\n", destposname);
    TRot3f rotMtx;
    rotMtx.identity();
    MR::makeMtxRotate(rotMtx, mRotation);

    rotMtx.getXDir(mSide);
    rotMtx.getYDir(mUp);
    rotMtx.getZDir(mFront);

    mBaseUp.set(mUp);
    mBaseSide.set(mSide);

    mRotation.zero();
    mVelocity.zero();
    mOrthoVelocity.zero();

    MR::makeMtxUpFrontPos(&mEffectHostMtx, -mGravity, mFront, mTranslation);
    return true;
}

void SurfRay::exePlayerExit() {
    if (MR::isFirstStep(this)) {
        MR::invalidateHitSensors(this);
        MR::invalidateClipping(this);

        MR::startBck(this, "Wait", nullptr);
        MR::tryEmitEffect(this, "Ripple");
        MR::tryDeleteEffect(this, "RunDashSplash");
        MR::tryDeleteEffect(this, "SwimSplash");


        TVec3f jumpPower(mFront);
        jumpPower.scale(-10.0f);
        jumpPower += mGravity * -35.0f;

        if (mDamageDismount != 0)
            MR::endBindAndPlayerDamageMsg(this, mDamageDismount, jumpPower);
        else {
            MR::startBckPlayer("SwingRopeSpin", nullptr);
            __kAutoMap_80050D60("JumpFromYoshi", -1, -1);
            MR::endBindAndPlayerForceJump(this, jumpPower, 0);
        }
    }

    //mIsDive = false;
    MR::calcGravity(this);
    updateToWater();
    updateInfo();
    updateToMap();
    updateSound();
    mOrthoVelocity.scale(0.5f);
    mSurfSpeed = 0.0f;
    mRotation.z = 0.0f;

    if (MR::isGreaterStep(this, 120)) {
        //resetAllInfo();
        MR::validateHitSensors(this);
        mRider = nullptr;
        setNerve(&NrvSurfRay::SurfRayNrvWait::sInstance);
    }
}

void SurfRay::updateDive() {
     if (!mConst->mIsDiveEnabled) {
         mIsDive = false;
         return;
     }

    if (PSVECDistance(mWaterPosition, mTranslation) < 120.0f)
        mIsDive = false;

    if (!mWaterInfo.isInWater()) {
        mIsDive = false;
        mDiveSpeed = 0.0f;
        return;
    }

    if (MR::testSubPadButtonZ(mPadChannel)) {
        mIsDive = true;

        TVec3f accel;
        calcRotateAccel(&accel);
        // Motion controls represent the physical motion of pointing down as the Y axis
        // The stick position is stored in X and Z
        f32 diveaccel = mConst->mIsStickControl ? accel.z : accel.y;

        if (MR::isNearZero(diveaccel, 0.1f))
            mDiveSpeed *= 0.5;
        else
            mDiveSpeed += mConst->mDiveAccel * diveaccel;
    }
    else {
        mDiveSpeed *= 0.5;
    }

    mDiveSpeed = MR::clamp(mDiveSpeed, -mConst->mDiveSpeedMax, mConst->mDiveSpeedMax);

    //OSReport("Dive 0 %s [%ff %ff %ff]\n", mIsDive ? "true" : "false", mOrthoVelocity.x, mOrthoVelocity.y, mOrthoVelocity.z);
    if (!MR::isNearZero(mDiveSpeed, 0.01f)) {
        mOrthoVelocity.add(mGravity * mDiveSpeed);
    }

    //OSReport("Dive 1 %s [%ff %ff %ff]\n", mIsDive ? "true":"false", mOrthoVelocity.x, mOrthoVelocity.y, mOrthoVelocity.z);
}

void SurfRay::updateEffect() {
    if (!mWaterInfo.isInWater()) {
        MR::tryDeleteEffect(this, "SwimSplash");
        MR::tryDeleteEffect(this, "RunDashSplash");
        MR::tryDeleteEffect(this, "Ripple");
    } else if (mSurfSpeed > mConst->mSpeedToEmitEffectFast) {
        MR::tryEmitEffect(this, "RunDashSplash");
        MR::tryDeleteEffect(this, "SwimSplash");
        MR::tryDeleteEffect(this, "Ripple");
    } else if (mSurfSpeed > mConst->mSpeedToEmitEffect || !MR::isNearZero(mDiveSpeed, 0.01f)) {
        MR::tryEmitEffect(this, "SwimSplash");
        MR::tryDeleteEffect(this, "RunDashSplash");
        MR::tryDeleteEffect(this, "Ripple");
    } else {
        MR::tryEmitEffect(this, "Ripple");
        MR::tryDeleteEffect(this, "RunDashSplash");
        MR::tryDeleteEffect(this, "SwimSplash");
        MR::makeMtxUpFrontPos(&mEffectHostMtx, -mGravity, mFront, mWaterInfo.mSurfacePos);
    }
}

void SurfRay::calcRotateAccel(TVec3f *pOut) const {
    if (mConst->mIsStickControl) {
        pOut->x = MR::getSubPadStickX(mPadChannel);
        pOut->z = MR::getSubPadStickY(mPadChannel);
    }
    else {
        MR::getCorePadAcceleration(pOut, mPadChannel);
    }
}

bool SurfRay::canBind() const {
    if (isNerve(&NrvSurfRay::SurfRayNrvPlayerExit::sInstance))
        return false;

    return !MR::isPlayerElementModeYoshi()
        && !MR::isPlayerInRush()
        && !MR::isPlayerRecovering();
}


// Hopefully sends out the message
kmCall(0x80294490, MR::isSensorPlayerOrRide);