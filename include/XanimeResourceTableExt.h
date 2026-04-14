
// credit to Petari
class XanimeBckTable {
public:
    const char* animationName;
};

class XanimeSingleBckTable {
public:
    XanimeBckTable parent;  // 0x0

    const char* fileName;  // 0x4
    u32 animationHash;     // 0x8
    u32 fileHash;          // 0xC
};


class XanimeTripleBckTable {
public:
    XanimeBckTable parent;  // 0x0

    const char* fileName1;  // 0x4
    f32 _8;

    const char* fileName2;  // 0xC
    f32 _10;

    const char* fileName3;  // 0x14;
    f32 _18;
};

struct XanimeGroupInfo {
    XanimeBckTable mParent;  // 0x0
    f32 _4;
    u32 _8;
    f32 _C;
    f32 _10;
    f32 _14;
    u32 _18;
    u8 _1C;
    u8 _1D;
    u32 _20[4];
    f32 _30[4];
    u32 _40;
    u32 _44;
};


XanimeGroupInfo cNewGroupInfos[] = {
    { "サーフィン", 1.0f, 0xF, 0, 0, 0, 0, 0, 0, {0,0,0,0}, {0,0,0,0}, 0, 0 },
    { "サーフィン（加速）", 1.0f, 0xF, 0, 0, 0, 0, 0, 0, {0,0,0,0}, {0,0,0,0}, 0, 0 },
    { "サーフィン傾き開始", 1.0f, 0x4, 0, 0, 0, 0, 0, 0, {0,0,0,0}, {0,0,0,0}, 0, 0 },
    { "サーフィン傾き開始（加速）", 1.0f, 0x4, 0, 0, 0, 0, 0, 0, {0,0,0,0}, {0,0,0,0}, 0, 0 },
    { "サーフィン落下", 1.0f, 0xF, 0, 0, 0, 0, 0, 0, {0,0,0,0}, {0,0,0,0}, 0, 0 },
    { "サーフィンジャンプ", 1.0f, 0x1, 0, 0, 0, 0, 0, 0, {0,0,0,0}, {0,0,0,0}, 0, 0 },
    { "サーフィンハイジャンプ", 1.0f, 0x6, 0, 0, 0, 0, 0, 0, {0,0,0,0}, {0,0,0,0}, 0, 0 },
    { "サーフィン着地", 1.0f, 0x1, 0, 0, 0, 0, 0, 0, {0,0,0,0}, {0,0,0,0}, 0, 0 },
    { "", 0.0f, 0, 0, 0, 0, 0, 0, 0, {0,0,0,0}, {0,0,0,0}, 0, 0 }
};

const size_t gGroupInfosEnries = sizeof(cNewGroupInfos)/sizeof(cNewGroupInfos[1])-1;

XanimeSingleBckTable extSingleAnimeTable[] = {
{ {"サーフィンジャンプ"}, "SurfJump", 0, 0 },
{ {"サーフィンハイジャンプ"}, "SurfJumpHigh", 0, 0 },
{ {"サーフィン着地"}, "SurfLand", 0, 0 },
{ {""}, "", 0, 0 }
};

XanimeTripleBckTable extTripleAnimeTable[] = {
    { {"坂左右ウエイト"}, "Wait", 1.0f, "WaitSlopeL", 0.0f, "WaitSlopeR", 0.0f },
    { {"坂前後ウエイト"}, "Wait", 1.0f, "WaitSlopeD", 0.0f, "WaitSlopeU", 0.0f },
    { {"チューブスライダー"}, "TubeSlide", 1.0f, "TubeSlideLeft", 0.0f, "TubeSlideRight", 0.0f },
    { {"グライバード滑空Wait"}, "GliBirdGlideWait", 1.0f, "GliBirdGlideTurnL", 0.0f, "GliBirdGlideTurnR", 0.0f },
    { {"グライバード滑空Down"}, "GliBirdGlideDown", 1.0f, "GliBirdGlideTurnL", 0.0f, "GliBirdGlideTurnR", 0.0f },
    { {"グライバード滑空Fast"}, "GliBirdGlideDownFast", 1.0f, "GliBirdGlideTurnL", 0.0f, "GliBirdGlideTurnR", 0.0f },
    { {"グライバード滑空Up"}, "GliBirdGlideUp", 1.0f, "GliBirdGlideTurnL", 0.0f, "GliBirdGlideTurnL", 0.0f },
    { {"サーフィン"}, "SurfRideLoop", 1.0f, "SurfRideLoopL", 0.0f, "SurfRideLoopR", 0.0f },
    { {"サーフィン（加速）"}, "SurfRideDashLoop", 1.0f, "SurfRideDashLoopL", 0.0f, "SurfRideDashLoopR", 0.0f },
    { {"サーフィン傾き開始"}, "SurfRide", 1.0f, "SurfRideL", 0.0f, "SurfRideR", 0.0f },
    { {"サーフィン傾き開始（加速）"}, "SurfRideDash", 1.0f, "SurfRideDashL", 0.0f, "SurfRideDashR", 0.0f },
    { {"サーフィン落下"}, "SurfFall", 1.0f, "SurfFallL", 0.0f, "SurfFallR", 0.0f },
    { {""}, "", 0.0f, nullptr, 0.0f, nullptr, 0.0f }
};