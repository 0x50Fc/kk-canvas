//
//  WebGLContextJS.cc
//  KKCanvas
//
//  Created by zhanghailong on 2018/9/28.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "WebGLContext.h"



namespace kk {
    
    
    namespace WebGL {
        
        IMP_SCRIPT_CLASS_BEGIN_NOALLOC(nullptr, Context, WebGLContext)
        
        /* ClearBufferMask */
        IMP_SCRIPT_CONST_UINT(DEPTH_BUFFER_BIT               , 0x00000100)
        IMP_SCRIPT_CONST_UINT(STENCIL_BUFFER_BIT             , 0x00000400)
        IMP_SCRIPT_CONST_UINT(COLOR_BUFFER_BIT               , 0x00004000)
        
        /* BeginMode */
        IMP_SCRIPT_CONST_UINT(POINTS                         , 0x0000)
        IMP_SCRIPT_CONST_UINT(LINES                          , 0x0001)
        IMP_SCRIPT_CONST_UINT(LINE_LOOP                      , 0x0002)
        IMP_SCRIPT_CONST_UINT(LINE_STRIP                     , 0x0003)
        IMP_SCRIPT_CONST_UINT(TRIANGLES                      , 0x0004)
        IMP_SCRIPT_CONST_UINT(TRIANGLE_STRIP                 , 0x0005)
        IMP_SCRIPT_CONST_UINT(TRIANGLE_FAN                   , 0x0006)
        
        /* AlphaFunction (not supported in ES20) */
        /*      NEVER */
        /*      LESS */
        /*      EQUAL */
        /*      LEQUAL */
        /*      GREATER */
        /*      NOTEQUAL */
        /*      GEQUAL */
        /*      ALWAYS */
        
        /* BlendingFactorDest */
        IMP_SCRIPT_CONST_UINT(ZERO                           , 0)
        IMP_SCRIPT_CONST_UINT(ONE                            , 1)
        IMP_SCRIPT_CONST_UINT(SRC_COLOR                      , 0x0300)
        IMP_SCRIPT_CONST_UINT(ONE_MINUS_SRC_COLOR            , 0x0301)
        IMP_SCRIPT_CONST_UINT(SRC_ALPHA                      , 0x0302)
        IMP_SCRIPT_CONST_UINT(ONE_MINUS_SRC_ALPHA            , 0x0303)
        IMP_SCRIPT_CONST_UINT(DST_ALPHA                      , 0x0304)
        IMP_SCRIPT_CONST_UINT(ONE_MINUS_DST_ALPHA            , 0x0305)
        
        /* BlendingFactorSrc */
        /*      ZERO */
        /*      ONE */
        IMP_SCRIPT_CONST_UINT(DST_COLOR                      , 0x0306)
        IMP_SCRIPT_CONST_UINT(ONE_MINUS_DST_COLOR            , 0x0307)
        IMP_SCRIPT_CONST_UINT(SRC_ALPHA_SATURATE             , 0x0308)
        /*      SRC_ALPHA */
        /*      ONE_MINUS_SRC_ALPHA */
        /*      DST_ALPHA */
        /*      ONE_MINUS_DST_ALPHA */
        
        /* BlendEquationSeparate */
        IMP_SCRIPT_CONST_UINT(FUNC_ADD                       , 0x8006)
        IMP_SCRIPT_CONST_UINT(BLEND_EQUATION                 , 0x8009)
        IMP_SCRIPT_CONST_UINT(BLEND_EQUATION_RGB             , 0x8009)   /* same as BLEND_EQUATION */
        IMP_SCRIPT_CONST_UINT(BLEND_EQUATION_ALPHA           , 0x883D)
        
        /* BlendSubtract */
        IMP_SCRIPT_CONST_UINT(FUNC_SUBTRACT                  , 0x800A)
        IMP_SCRIPT_CONST_UINT(FUNC_REVERSE_SUBTRACT          , 0x800B)
        
        /* Separate Blend Functions */
        IMP_SCRIPT_CONST_UINT(BLEND_DST_RGB                  , 0x80C8)
        IMP_SCRIPT_CONST_UINT(BLEND_SRC_RGB                  , 0x80C9)
        IMP_SCRIPT_CONST_UINT(BLEND_DST_ALPHA                , 0x80CA)
        IMP_SCRIPT_CONST_UINT(BLEND_SRC_ALPHA                , 0x80CB)
        IMP_SCRIPT_CONST_UINT(CONSTANT_COLOR                 , 0x8001)
        IMP_SCRIPT_CONST_UINT(ONE_MINUS_CONSTANT_COLOR       , 0x8002)
        IMP_SCRIPT_CONST_UINT(CONSTANT_ALPHA                 , 0x8003)
        IMP_SCRIPT_CONST_UINT(ONE_MINUS_CONSTANT_ALPHA       , 0x8004)
        IMP_SCRIPT_CONST_UINT(BLEND_COLOR                    , 0x8005)
        
        /* Buffer Objects */
        IMP_SCRIPT_CONST_UINT(ARRAY_BUFFER                   , 0x8892)
        IMP_SCRIPT_CONST_UINT(ELEMENT_ARRAY_BUFFER           , 0x8893)
        IMP_SCRIPT_CONST_UINT(ARRAY_BUFFER_BINDING           , 0x8894)
        IMP_SCRIPT_CONST_UINT(ELEMENT_ARRAY_BUFFER_BINDING   , 0x8895)
        
        IMP_SCRIPT_CONST_UINT(STREAM_DRAW                    , 0x88E0)
        IMP_SCRIPT_CONST_UINT(STATIC_DRAW                    , 0x88E4)
        IMP_SCRIPT_CONST_UINT(DYNAMIC_DRAW                   , 0x88E8)
        
        IMP_SCRIPT_CONST_UINT(BUFFER_SIZE                    , 0x8764)
        IMP_SCRIPT_CONST_UINT(BUFFER_USAGE                   , 0x8765)
        
        IMP_SCRIPT_CONST_UINT(CURRENT_VERTEX_ATTRIB          , 0x8626)
        
        /* CullFaceMode */
        IMP_SCRIPT_CONST_UINT(FRONT                          , 0x0404)
        IMP_SCRIPT_CONST_UINT(BACK                           , 0x0405)
        IMP_SCRIPT_CONST_UINT(FRONT_AND_BACK                 , 0x0408)
        
        /* DepthFunction */
        /*      NEVER */
        /*      LESS */
        /*      EQUAL */
        /*      LEQUAL */
        /*      GREATER */
        /*      NOTEQUAL */
        /*      GEQUAL */
        /*      ALWAYS */
        
        /* EnableCap */
        /* TEXTURE_2D */
        IMP_SCRIPT_CONST_UINT(CULL_FACE                      , 0x0B44)
        IMP_SCRIPT_CONST_UINT(BLEND                          , 0x0BE2)
        IMP_SCRIPT_CONST_UINT(DITHER                         , 0x0BD0)
        IMP_SCRIPT_CONST_UINT(STENCIL_TEST                   , 0x0B90)
        IMP_SCRIPT_CONST_UINT(DEPTH_TEST                     , 0x0B71)
        IMP_SCRIPT_CONST_UINT(SCISSOR_TEST                   , 0x0C11)
        IMP_SCRIPT_CONST_UINT(POLYGON_OFFSET_FILL            , 0x8037)
        IMP_SCRIPT_CONST_UINT(SAMPLE_ALPHA_TO_COVERAGE       , 0x809E)
        IMP_SCRIPT_CONST_UINT(SAMPLE_COVERAGE                , 0x80A0)
        
        /* ErrorCode */
        IMP_SCRIPT_CONST_UINT(NO_ERROR                       , 0)
        IMP_SCRIPT_CONST_UINT(INVALID_ENUM                   , 0x0500)
        IMP_SCRIPT_CONST_UINT(INVALID_VALUE                  , 0x0501)
        IMP_SCRIPT_CONST_UINT(INVALID_OPERATION              , 0x0502)
        IMP_SCRIPT_CONST_UINT(OUT_OF_MEMORY                  , 0x0505)
        
        /* FrontFaceDirection */
        IMP_SCRIPT_CONST_UINT(CW                             , 0x0900)
        IMP_SCRIPT_CONST_UINT(CCW                            , 0x0901)
        
        /* GetPName */
        IMP_SCRIPT_CONST_UINT(LINE_WIDTH                     , 0x0B21)
        IMP_SCRIPT_CONST_UINT(ALIASED_POINT_SIZE_RANGE       , 0x846D)
        IMP_SCRIPT_CONST_UINT(ALIASED_LINE_WIDTH_RANGE       , 0x846E)
        IMP_SCRIPT_CONST_UINT(CULL_FACE_MODE                 , 0x0B45)
        IMP_SCRIPT_CONST_UINT(FRONT_FACE                     , 0x0B46)
        IMP_SCRIPT_CONST_UINT(DEPTH_RANGE                    , 0x0B70)
        IMP_SCRIPT_CONST_UINT(DEPTH_WRITEMASK                , 0x0B72)
        IMP_SCRIPT_CONST_UINT(DEPTH_CLEAR_VALUE              , 0x0B73)
        IMP_SCRIPT_CONST_UINT(DEPTH_FUNC                     , 0x0B74)
        IMP_SCRIPT_CONST_UINT(STENCIL_CLEAR_VALUE            , 0x0B91)
        IMP_SCRIPT_CONST_UINT(STENCIL_FUNC                   , 0x0B92)
        IMP_SCRIPT_CONST_UINT(STENCIL_FAIL                   , 0x0B94)
        IMP_SCRIPT_CONST_UINT(STENCIL_PASS_DEPTH_FAIL        , 0x0B95)
        IMP_SCRIPT_CONST_UINT(STENCIL_PASS_DEPTH_PASS        , 0x0B96)
        IMP_SCRIPT_CONST_UINT(STENCIL_REF                    , 0x0B97)
        IMP_SCRIPT_CONST_UINT(STENCIL_VALUE_MASK             , 0x0B93)
        IMP_SCRIPT_CONST_UINT(STENCIL_WRITEMASK              , 0x0B98)
        IMP_SCRIPT_CONST_UINT(STENCIL_BACK_FUNC              , 0x8800)
        IMP_SCRIPT_CONST_UINT(STENCIL_BACK_FAIL              , 0x8801)
        IMP_SCRIPT_CONST_UINT(STENCIL_BACK_PASS_DEPTH_FAIL   , 0x8802)
        IMP_SCRIPT_CONST_UINT(STENCIL_BACK_PASS_DEPTH_PASS   , 0x8803)
        IMP_SCRIPT_CONST_UINT(STENCIL_BACK_REF               , 0x8CA3)
        IMP_SCRIPT_CONST_UINT(STENCIL_BACK_VALUE_MASK        , 0x8CA4)
        IMP_SCRIPT_CONST_UINT(STENCIL_BACK_WRITEMASK         , 0x8CA5)
        IMP_SCRIPT_CONST_UINT(VIEWPORT                       , 0x0BA2)
        IMP_SCRIPT_CONST_UINT(SCISSOR_BOX                    , 0x0C10)
        /*      SCISSOR_TEST */
        IMP_SCRIPT_CONST_UINT(COLOR_CLEAR_VALUE              , 0x0C22)
        IMP_SCRIPT_CONST_UINT(COLOR_WRITEMASK                , 0x0C23)
        IMP_SCRIPT_CONST_UINT(UNPACK_ALIGNMENT               , 0x0CF5)
        IMP_SCRIPT_CONST_UINT(PACK_ALIGNMENT                 , 0x0D05)
        IMP_SCRIPT_CONST_UINT(MAX_TEXTURE_SIZE               , 0x0D33)
        IMP_SCRIPT_CONST_UINT(MAX_VIEWPORT_DIMS              , 0x0D3A)
        IMP_SCRIPT_CONST_UINT(SUBPIXEL_BITS                  , 0x0D50)
        IMP_SCRIPT_CONST_UINT(RED_BITS                       , 0x0D52)
        IMP_SCRIPT_CONST_UINT(GREEN_BITS                     , 0x0D53)
        IMP_SCRIPT_CONST_UINT(BLUE_BITS                      , 0x0D54)
        IMP_SCRIPT_CONST_UINT(ALPHA_BITS                     , 0x0D55)
        IMP_SCRIPT_CONST_UINT(DEPTH_BITS                     , 0x0D56)
        IMP_SCRIPT_CONST_UINT(STENCIL_BITS                   , 0x0D57)
        IMP_SCRIPT_CONST_UINT(POLYGON_OFFSET_UNITS           , 0x2A00)
        /*      POLYGON_OFFSET_FILL */
        IMP_SCRIPT_CONST_UINT(POLYGON_OFFSET_FACTOR          , 0x8038)
        IMP_SCRIPT_CONST_UINT(TEXTURE_BINDING_2D             , 0x8069)
        IMP_SCRIPT_CONST_UINT(SAMPLE_BUFFERS                 , 0x80A8)
        IMP_SCRIPT_CONST_UINT(SAMPLES                        , 0x80A9)
        IMP_SCRIPT_CONST_UINT(SAMPLE_COVERAGE_VALUE          , 0x80AA)
        IMP_SCRIPT_CONST_UINT(SAMPLE_COVERAGE_INVERT         , 0x80AB)
        
        /* GetTextureParameter */
        /*      TEXTURE_MAG_FILTER */
        /*      TEXTURE_MIN_FILTER */
        /*      TEXTURE_WRAP_S */
        /*      TEXTURE_WRAP_T */
        
        IMP_SCRIPT_CONST_UINT(COMPRESSED_TEXTURE_FORMATS     , 0x86A3)
        
        /* HintMode */
        IMP_SCRIPT_CONST_UINT(DONT_CARE                      , 0x1100)
        IMP_SCRIPT_CONST_UINT(FASTEST                        , 0x1101)
        IMP_SCRIPT_CONST_UINT(NICEST                         , 0x1102)
        
        /* HintTarget */
        IMP_SCRIPT_CONST_UINT(GENERATE_MIPMAP_HINT            , 0x8192)
        
        /* DataType */
        IMP_SCRIPT_CONST_UINT(BYTE                           , 0x1400)
        IMP_SCRIPT_CONST_UINT(UNSIGNED_BYTE                  , 0x1401)
        IMP_SCRIPT_CONST_UINT(SHORT                          , 0x1402)
        IMP_SCRIPT_CONST_UINT(UNSIGNED_SHORT                 , 0x1403)
        IMP_SCRIPT_CONST_UINT(INT                            , 0x1404)
        IMP_SCRIPT_CONST_UINT(UNSIGNED_INT                   , 0x1405)
        IMP_SCRIPT_CONST_UINT(FLOAT                          , 0x1406)
        
        /* PixelFormat */
        IMP_SCRIPT_CONST_UINT(DEPTH_COMPONENT                , 0x1902)
        IMP_SCRIPT_CONST_UINT(ALPHA                          , 0x1906)
        IMP_SCRIPT_CONST_UINT(RGB                            , 0x1907)
        IMP_SCRIPT_CONST_UINT(RGBA                           , 0x1908)
        IMP_SCRIPT_CONST_UINT(LUMINANCE                      , 0x1909)
        IMP_SCRIPT_CONST_UINT(LUMINANCE_ALPHA                , 0x190A)
        
        /* PixelType */
        /*      UNSIGNED_BYTE */
        IMP_SCRIPT_CONST_UINT(UNSIGNED_SHORT_4_4_4_4         , 0x8033)
        IMP_SCRIPT_CONST_UINT(UNSIGNED_SHORT_5_5_5_1         , 0x8034)
        IMP_SCRIPT_CONST_UINT(UNSIGNED_SHORT_5_6_5           , 0x8363)
        
        /* Shaders */
        IMP_SCRIPT_CONST_UINT(FRAGMENT_SHADER                  , 0x8B30)
        IMP_SCRIPT_CONST_UINT(VERTEX_SHADER                    , 0x8B31)
        IMP_SCRIPT_CONST_UINT(MAX_VERTEX_ATTRIBS               , 0x8869)
        IMP_SCRIPT_CONST_UINT(MAX_VERTEX_UNIFORM_VECTORS       , 0x8DFB)
        IMP_SCRIPT_CONST_UINT(MAX_VARYING_VECTORS              , 0x8DFC)
        IMP_SCRIPT_CONST_UINT(MAX_COMBINED_TEXTURE_IMAGE_UNITS , 0x8B4D)
        IMP_SCRIPT_CONST_UINT(MAX_VERTEX_TEXTURE_IMAGE_UNITS   , 0x8B4C)
        IMP_SCRIPT_CONST_UINT(MAX_TEXTURE_IMAGE_UNITS          , 0x8872)
        IMP_SCRIPT_CONST_UINT(MAX_FRAGMENT_UNIFORM_VECTORS     , 0x8DFD)
        IMP_SCRIPT_CONST_UINT(SHADER_TYPE                      , 0x8B4F)
        IMP_SCRIPT_CONST_UINT(DELETE_STATUS                    , 0x8B80)
        IMP_SCRIPT_CONST_UINT(LINK_STATUS                      , 0x8B82)
        IMP_SCRIPT_CONST_UINT(VALIDATE_STATUS                  , 0x8B83)
        IMP_SCRIPT_CONST_UINT(ATTACHED_SHADERS                 , 0x8B85)
        IMP_SCRIPT_CONST_UINT(ACTIVE_UNIFORMS                  , 0x8B86)
        IMP_SCRIPT_CONST_UINT(ACTIVE_ATTRIBUTES                , 0x8B89)
        IMP_SCRIPT_CONST_UINT(SHADING_LANGUAGE_VERSION         , 0x8B8C)
        IMP_SCRIPT_CONST_UINT(CURRENT_PROGRAM                  , 0x8B8D)
        
        /* StencilFunction */
        IMP_SCRIPT_CONST_UINT(NEVER                          , 0x0200)
        IMP_SCRIPT_CONST_UINT(LESS                           , 0x0201)
        IMP_SCRIPT_CONST_UINT(EQUAL                          , 0x0202)
        IMP_SCRIPT_CONST_UINT(LEQUAL                         , 0x0203)
        IMP_SCRIPT_CONST_UINT(GREATER                        , 0x0204)
        IMP_SCRIPT_CONST_UINT(NOTEQUAL                       , 0x0205)
        IMP_SCRIPT_CONST_UINT(GEQUAL                         , 0x0206)
        IMP_SCRIPT_CONST_UINT(ALWAYS                         , 0x0207)
        
        /* StencilOp */
        /*      ZERO */
        IMP_SCRIPT_CONST_UINT(KEEP                           , 0x1E00)
        IMP_SCRIPT_CONST_UINT(REPLACE                        , 0x1E01)
        IMP_SCRIPT_CONST_UINT(INCR                           , 0x1E02)
        IMP_SCRIPT_CONST_UINT(DECR                           , 0x1E03)
        IMP_SCRIPT_CONST_UINT(INVERT                         , 0x150A)
        IMP_SCRIPT_CONST_UINT(INCR_WRAP                      , 0x8507)
        IMP_SCRIPT_CONST_UINT(DECR_WRAP                      , 0x8508)
        
        /* StringName */
        IMP_SCRIPT_CONST_UINT(VENDOR                         , 0x1F00)
        IMP_SCRIPT_CONST_UINT(RENDERER                       , 0x1F01)
        IMP_SCRIPT_CONST_UINT(VERSION                        , 0x1F02)
        
        /* TextureMagFilter */
        IMP_SCRIPT_CONST_UINT(NEAREST                        , 0x2600)
        IMP_SCRIPT_CONST_UINT(LINEAR                         , 0x2601)
        
        /* TextureMinFilter */
        /*      NEAREST */
        /*      LINEAR */
        IMP_SCRIPT_CONST_UINT(NEAREST_MIPMAP_NEAREST         , 0x2700)
        IMP_SCRIPT_CONST_UINT(LINEAR_MIPMAP_NEAREST          , 0x2701)
        IMP_SCRIPT_CONST_UINT(NEAREST_MIPMAP_LINEAR          , 0x2702)
        IMP_SCRIPT_CONST_UINT(LINEAR_MIPMAP_LINEAR           , 0x2703)
        
        /* TextureParameterName */
        IMP_SCRIPT_CONST_UINT(TEXTURE_MAG_FILTER             , 0x2800)
        IMP_SCRIPT_CONST_UINT(TEXTURE_MIN_FILTER             , 0x2801)
        IMP_SCRIPT_CONST_UINT(TEXTURE_WRAP_S                 , 0x2802)
        IMP_SCRIPT_CONST_UINT(TEXTURE_WRAP_T                 , 0x2803)
        
        /* TextureTarget */
        IMP_SCRIPT_CONST_UINT(TEXTURE_2D                     , 0x0DE1)
        IMP_SCRIPT_CONST_UINT(TEXTURE                        , 0x1702)
        
        IMP_SCRIPT_CONST_UINT(TEXTURE_CUBE_MAP               , 0x8513)
        IMP_SCRIPT_CONST_UINT(TEXTURE_BINDING_CUBE_MAP       , 0x8514)
        IMP_SCRIPT_CONST_UINT(TEXTURE_CUBE_MAP_POSITIVE_X    , 0x8515)
        IMP_SCRIPT_CONST_UINT(TEXTURE_CUBE_MAP_NEGATIVE_X    , 0x8516)
        IMP_SCRIPT_CONST_UINT(TEXTURE_CUBE_MAP_POSITIVE_Y    , 0x8517)
        IMP_SCRIPT_CONST_UINT(TEXTURE_CUBE_MAP_NEGATIVE_Y    , 0x8518)
        IMP_SCRIPT_CONST_UINT(TEXTURE_CUBE_MAP_POSITIVE_Z    , 0x8519)
        IMP_SCRIPT_CONST_UINT(TEXTURE_CUBE_MAP_NEGATIVE_Z    , 0x851A)
        IMP_SCRIPT_CONST_UINT(MAX_CUBE_MAP_TEXTURE_SIZE      , 0x851C)
        
        /* TextureUnit */
        IMP_SCRIPT_CONST_UINT(TEXTURE0                       , 0x84C0)
        IMP_SCRIPT_CONST_UINT(TEXTURE1                       , 0x84C1)
        IMP_SCRIPT_CONST_UINT(TEXTURE2                       , 0x84C2)
        IMP_SCRIPT_CONST_UINT(TEXTURE3                       , 0x84C3)
        IMP_SCRIPT_CONST_UINT(TEXTURE4                       , 0x84C4)
        IMP_SCRIPT_CONST_UINT(TEXTURE5                       , 0x84C5)
        IMP_SCRIPT_CONST_UINT(TEXTURE6                       , 0x84C6)
        IMP_SCRIPT_CONST_UINT(TEXTURE7                       , 0x84C7)
        IMP_SCRIPT_CONST_UINT(TEXTURE8                       , 0x84C8)
        IMP_SCRIPT_CONST_UINT(TEXTURE9                       , 0x84C9)
        IMP_SCRIPT_CONST_UINT(TEXTURE10                      , 0x84CA)
        IMP_SCRIPT_CONST_UINT(TEXTURE11                      , 0x84CB)
        IMP_SCRIPT_CONST_UINT(TEXTURE12                      , 0x84CC)
        IMP_SCRIPT_CONST_UINT(TEXTURE13                      , 0x84CD)
        IMP_SCRIPT_CONST_UINT(TEXTURE14                      , 0x84CE)
        IMP_SCRIPT_CONST_UINT(TEXTURE15                      , 0x84CF)
        IMP_SCRIPT_CONST_UINT(TEXTURE16                      , 0x84D0)
        IMP_SCRIPT_CONST_UINT(TEXTURE17                      , 0x84D1)
        IMP_SCRIPT_CONST_UINT(TEXTURE18                      , 0x84D2)
        IMP_SCRIPT_CONST_UINT(TEXTURE19                      , 0x84D3)
        IMP_SCRIPT_CONST_UINT(TEXTURE20                      , 0x84D4)
        IMP_SCRIPT_CONST_UINT(TEXTURE21                      , 0x84D5)
        IMP_SCRIPT_CONST_UINT(TEXTURE22                      , 0x84D6)
        IMP_SCRIPT_CONST_UINT(TEXTURE23                      , 0x84D7)
        IMP_SCRIPT_CONST_UINT(TEXTURE24                      , 0x84D8)
        IMP_SCRIPT_CONST_UINT(TEXTURE25                      , 0x84D9)
        IMP_SCRIPT_CONST_UINT(TEXTURE26                      , 0x84DA)
        IMP_SCRIPT_CONST_UINT(TEXTURE27                      , 0x84DB)
        IMP_SCRIPT_CONST_UINT(TEXTURE28                      , 0x84DC)
        IMP_SCRIPT_CONST_UINT(TEXTURE29                      , 0x84DD)
        IMP_SCRIPT_CONST_UINT(TEXTURE30                      , 0x84DE)
        IMP_SCRIPT_CONST_UINT(TEXTURE31                      , 0x84DF)
        IMP_SCRIPT_CONST_UINT(ACTIVE_TEXTURE                 , 0x84E0)
        
        /* TextureWrapMode */
        IMP_SCRIPT_CONST_UINT(REPEAT                         , 0x2901)
        IMP_SCRIPT_CONST_UINT(CLAMP_TO_EDGE                  , 0x812F)
        IMP_SCRIPT_CONST_UINT(MIRRORED_REPEAT                , 0x8370)
        
        /* Uniform Types */
        IMP_SCRIPT_CONST_UINT(FLOAT_VEC2                     , 0x8B50)
        IMP_SCRIPT_CONST_UINT(FLOAT_VEC3                     , 0x8B51)
        IMP_SCRIPT_CONST_UINT(FLOAT_VEC4                     , 0x8B52)
        IMP_SCRIPT_CONST_UINT(INT_VEC2                       , 0x8B53)
        IMP_SCRIPT_CONST_UINT(INT_VEC3                       , 0x8B54)
        IMP_SCRIPT_CONST_UINT(INT_VEC4                       , 0x8B55)
        IMP_SCRIPT_CONST_UINT(BOOL                           , 0x8B56)
        IMP_SCRIPT_CONST_UINT(BOOL_VEC2                      , 0x8B57)
        IMP_SCRIPT_CONST_UINT(BOOL_VEC3                      , 0x8B58)
        IMP_SCRIPT_CONST_UINT(BOOL_VEC4                      , 0x8B59)
        IMP_SCRIPT_CONST_UINT(FLOAT_MAT2                     , 0x8B5A)
        IMP_SCRIPT_CONST_UINT(FLOAT_MAT3                     , 0x8B5B)
        IMP_SCRIPT_CONST_UINT(FLOAT_MAT4                     , 0x8B5C)
        IMP_SCRIPT_CONST_UINT(SAMPLER_2D                     , 0x8B5E)
        IMP_SCRIPT_CONST_UINT(SAMPLER_CUBE                   , 0x8B60)
        
        /* Vertex Arrays */
        IMP_SCRIPT_CONST_UINT(VERTEX_ATTRIB_ARRAY_ENABLED        , 0x8622)
        IMP_SCRIPT_CONST_UINT(VERTEX_ATTRIB_ARRAY_SIZE           , 0x8623)
        IMP_SCRIPT_CONST_UINT(VERTEX_ATTRIB_ARRAY_STRIDE         , 0x8624)
        IMP_SCRIPT_CONST_UINT(VERTEX_ATTRIB_ARRAY_TYPE           , 0x8625)
        IMP_SCRIPT_CONST_UINT(VERTEX_ATTRIB_ARRAY_NORMALIZED     , 0x886A)
        IMP_SCRIPT_CONST_UINT(VERTEX_ATTRIB_ARRAY_POINTER        , 0x8645)
        IMP_SCRIPT_CONST_UINT(VERTEX_ATTRIB_ARRAY_BUFFER_BINDING , 0x889F)
        
        /* Read Format */
        IMP_SCRIPT_CONST_UINT(IMPLEMENTATION_COLOR_READ_TYPE   , 0x8B9A)
        IMP_SCRIPT_CONST_UINT(IMPLEMENTATION_COLOR_READ_FORMAT , 0x8B9B)
        
        /* Shader Source */
        IMP_SCRIPT_CONST_UINT(COMPILE_STATUS                 , 0x8B81)
        
        /* Shader Precision-Specified Types */
        IMP_SCRIPT_CONST_UINT(LOW_FLOAT                      , 0x8DF0)
        IMP_SCRIPT_CONST_UINT(MEDIUM_FLOAT                   , 0x8DF1)
        IMP_SCRIPT_CONST_UINT(HIGH_FLOAT                     , 0x8DF2)
        IMP_SCRIPT_CONST_UINT(LOW_INT                        , 0x8DF3)
        IMP_SCRIPT_CONST_UINT(MEDIUM_INT                     , 0x8DF4)
        IMP_SCRIPT_CONST_UINT(HIGH_INT                       , 0x8DF5)
        
        /* Framebuffer Object. */
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER                    , 0x8D40)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER                   , 0x8D41)
        
        IMP_SCRIPT_CONST_UINT(RGBA4                          , 0x8056)
        IMP_SCRIPT_CONST_UINT(RGB5_A1                        , 0x8057)
        IMP_SCRIPT_CONST_UINT(RGB565                         , 0x8D62)
        IMP_SCRIPT_CONST_UINT(DEPTH_COMPONENT16              , 0x81A5)
        IMP_SCRIPT_CONST_UINT(STENCIL_INDEX                  , 0x1901)
        IMP_SCRIPT_CONST_UINT(STENCIL_INDEX8                 , 0x8D48)
        IMP_SCRIPT_CONST_UINT(DEPTH_STENCIL                  , 0x84F9)
        
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_WIDTH             , 0x8D42)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_HEIGHT            , 0x8D43)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_INTERNAL_FORMAT   , 0x8D44)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_RED_SIZE          , 0x8D50)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_GREEN_SIZE        , 0x8D51)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_BLUE_SIZE         , 0x8D52)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_ALPHA_SIZE        , 0x8D53)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_DEPTH_SIZE        , 0x8D54)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_STENCIL_SIZE      , 0x8D55)
        
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE           , 0x8CD0)
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_ATTACHMENT_OBJECT_NAME           , 0x8CD1)
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL         , 0x8CD2)
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE , 0x8CD3)
        
        IMP_SCRIPT_CONST_UINT(COLOR_ATTACHMENT0              , 0x8CE0)
        IMP_SCRIPT_CONST_UINT(DEPTH_ATTACHMENT               , 0x8D00)
        IMP_SCRIPT_CONST_UINT(STENCIL_ATTACHMENT             , 0x8D20)
        IMP_SCRIPT_CONST_UINT(DEPTH_STENCIL_ATTACHMENT       , 0x821A)
        
        IMP_SCRIPT_CONST_UINT(NONE                           , 0)
        
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_COMPLETE                      , 0x8CD5)
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_INCOMPLETE_ATTACHMENT         , 0x8CD6)
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT , 0x8CD7)
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_INCOMPLETE_DIMENSIONS         , 0x8CD9)
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_UNSUPPORTED                   , 0x8CDD)
        
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_BINDING            , 0x8CA6)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_BINDING           , 0x8CA7)
        IMP_SCRIPT_CONST_UINT(MAX_RENDERBUFFER_SIZE          , 0x84E8)
        
        IMP_SCRIPT_CONST_UINT(INVALID_FRAMEBUFFER_OPERATION  , 0x0506)
        
        /* WebGL-specific enums */
        IMP_SCRIPT_CONST_UINT(UNPACK_FLIP_Y_WEBGL            , 0x9240)
        IMP_SCRIPT_CONST_UINT(UNPACK_PREMULTIPLY_ALPHA_WEBGL , 0x9241)
        IMP_SCRIPT_CONST_UINT(CONTEXT_LOST_WEBGL             , 0x9242)
        IMP_SCRIPT_CONST_UINT(UNPACK_COLORSPACE_CONVERSION_WEBGL , 0x9243)
        IMP_SCRIPT_CONST_UINT(BROWSER_DEFAULT_WEBGL          , 0x9244)
        
        
        static kk::script::Property propertys[] = {
            IMP_SCRIPT_PROPERTY_READONLY(Context,drawingBufferWidth)
            IMP_SCRIPT_PROPERTY_READONLY(Context,drawingBufferHeight)
        };
        
        kk::script::SetProperty(ctx, -1, propertys, sizeof(propertys) / sizeof(kk::script::Property));
        
        
        static kk::script::Method methods[] = {
            IMP_SCRIPT_METHOD(Context,activeTexture)
            IMP_SCRIPT_METHOD(Context,attachShader)
            IMP_SCRIPT_METHOD(Context,bindAttribLocation)
            IMP_SCRIPT_METHOD(Context,bindBuffer)
            IMP_SCRIPT_METHOD(Context,bindFramebuffer)
            IMP_SCRIPT_METHOD(Context,bindRenderbuffer)
            IMP_SCRIPT_METHOD(Context,bindTexture)
            IMP_SCRIPT_METHOD(Context,blendColor)
            IMP_SCRIPT_METHOD(Context,blendEquation)
            IMP_SCRIPT_METHOD(Context,blendEquationSeparate)
            IMP_SCRIPT_METHOD(Context,blendFunc)
            IMP_SCRIPT_METHOD(Context,blendFuncSeparate)
            IMP_SCRIPT_METHOD(Context,bufferData)
            IMP_SCRIPT_METHOD(Context,bufferSubData)
            IMP_SCRIPT_METHOD(Context,checkFramebufferStatus)
            IMP_SCRIPT_METHOD(Context,clear)
            IMP_SCRIPT_METHOD(Context,clearColor)
            IMP_SCRIPT_METHOD(Context,clearDepth)
            IMP_SCRIPT_METHOD(Context,clearStencil)
            IMP_SCRIPT_METHOD(Context,colorMask)
            IMP_SCRIPT_METHOD(Context,compileShader)
            IMP_SCRIPT_METHOD(Context,compressedTexImage2D)
            IMP_SCRIPT_METHOD(Context,compressedTexSubImage2D)
            IMP_SCRIPT_METHOD(Context,copyTexImage2D)
            IMP_SCRIPT_METHOD(Context,copyTexSubImage2D)
            
            IMP_SCRIPT_METHOD(Context,createBuffer)
            IMP_SCRIPT_METHOD(Context,createFramebuffer)
            IMP_SCRIPT_METHOD(Context,createProgram)
            IMP_SCRIPT_METHOD(Context,createRenderbuffer)
            IMP_SCRIPT_METHOD(Context,createShader)
            IMP_SCRIPT_METHOD(Context,createTexture)
            
            IMP_SCRIPT_METHOD(Context,cullFace)
            
            IMP_SCRIPT_METHOD(Context,deleteBuffer)
            IMP_SCRIPT_METHOD(Context,deleteFramebuffer)
            IMP_SCRIPT_METHOD(Context,deleteProgram)
            IMP_SCRIPT_METHOD(Context,deleteRenderbuffer)
            IMP_SCRIPT_METHOD(Context,deleteShader)
            IMP_SCRIPT_METHOD(Context,deleteTexture)
            
            IMP_SCRIPT_METHOD(Context,depthFunc)
            IMP_SCRIPT_METHOD(Context,depthMask)
            IMP_SCRIPT_METHOD(Context,depthRange)
            IMP_SCRIPT_METHOD(Context,detachShader)
            IMP_SCRIPT_METHOD(Context,disable)
            IMP_SCRIPT_METHOD(Context,disableVertexAttribArray)
            IMP_SCRIPT_METHOD(Context,drawArrays)
            IMP_SCRIPT_METHOD(Context,drawElements)
            
            IMP_SCRIPT_METHOD(Context,enable)
            IMP_SCRIPT_METHOD(Context,enableVertexAttribArray)
            IMP_SCRIPT_METHOD(Context,finish)
            IMP_SCRIPT_METHOD(Context,flush)
            IMP_SCRIPT_METHOD(Context,framebufferRenderbuffer)
            IMP_SCRIPT_METHOD(Context,framebufferTexture2D)
            IMP_SCRIPT_METHOD(Context,frontFace)
            
            IMP_SCRIPT_METHOD(Context,generateMipmap)
            
            IMP_SCRIPT_METHOD(Context,getActiveAttrib)
            IMP_SCRIPT_METHOD(Context,getActiveUniform)
            IMP_SCRIPT_METHOD(Context,getAttachedShaders)
            
            IMP_SCRIPT_METHOD(Context,getAttribLocation)
            
            IMP_SCRIPT_METHOD(Context,getBufferParameter)
            IMP_SCRIPT_METHOD(Context,getParameter)
            
            IMP_SCRIPT_METHOD(Context,getError)
            
            IMP_SCRIPT_METHOD(Context,getFramebufferAttachmentParameter)
            IMP_SCRIPT_METHOD(Context,getProgramParameter)
            IMP_SCRIPT_METHOD(Context,getProgramInfoLog)
            IMP_SCRIPT_METHOD(Context,getRenderbufferParameter)
            IMP_SCRIPT_METHOD(Context,getShaderParameter)
            IMP_SCRIPT_METHOD(Context,getShaderPrecisionFormat)
            IMP_SCRIPT_METHOD(Context,getShaderInfoLog)
            
            IMP_SCRIPT_METHOD(Context,getShaderSource)
            
            IMP_SCRIPT_METHOD(Context,getTexParameter)
            
            IMP_SCRIPT_METHOD(Context,getUniform)
            
            IMP_SCRIPT_METHOD(Context,getUniformLocation)
            
            IMP_SCRIPT_METHOD(Context,getVertexAttrib)
            
            IMP_SCRIPT_METHOD(Context,getVertexAttribOffset)
            
            IMP_SCRIPT_METHOD(Context,hint)
            IMP_SCRIPT_METHOD(Context,isBuffer)
            IMP_SCRIPT_METHOD(Context,isEnabled)
            IMP_SCRIPT_METHOD(Context,isFramebuffer)
            IMP_SCRIPT_METHOD(Context,isProgram)
            IMP_SCRIPT_METHOD(Context,isRenderbuffer)
            IMP_SCRIPT_METHOD(Context,isShader)
            IMP_SCRIPT_METHOD(Context,isTexture)
            IMP_SCRIPT_METHOD(Context,lineWidth)
            IMP_SCRIPT_METHOD(Context,linkProgram)
            IMP_SCRIPT_METHOD(Context,pixelStorei)
            IMP_SCRIPT_METHOD(Context,polygonOffset)
            
            IMP_SCRIPT_METHOD(Context,readPixels)
            
            IMP_SCRIPT_METHOD(Context,renderbufferStorage)
            IMP_SCRIPT_METHOD(Context,sampleCoverage)
            IMP_SCRIPT_METHOD(Context,scissor)
            
            IMP_SCRIPT_METHOD(Context,shaderSource)
            
            IMP_SCRIPT_METHOD(Context,stencilFunc)
            IMP_SCRIPT_METHOD(Context,stencilFuncSeparate)
            IMP_SCRIPT_METHOD(Context,stencilMask)
            IMP_SCRIPT_METHOD(Context,stencilMaskSeparate)
            IMP_SCRIPT_METHOD(Context,stencilOp)
            IMP_SCRIPT_METHOD(Context,stencilOpSeparate)
            
            IMP_SCRIPT_METHOD(Context,texImage2D)
            
            IMP_SCRIPT_METHOD(Context,texParameterf)
            IMP_SCRIPT_METHOD(Context,texParameteri)
            
            IMP_SCRIPT_METHOD(Context,texSubImage2D)
            
            IMP_SCRIPT_METHOD(Context,uniform1f)
            IMP_SCRIPT_METHOD(Context,uniform1fv)
            IMP_SCRIPT_METHOD(Context,uniform1i)
            IMP_SCRIPT_METHOD(Context,uniform1iv)
            IMP_SCRIPT_METHOD(Context,uniform2f)
            IMP_SCRIPT_METHOD(Context,uniform2fv)
            IMP_SCRIPT_METHOD(Context,uniform2i)
            IMP_SCRIPT_METHOD(Context,uniform2iv)
            IMP_SCRIPT_METHOD(Context,uniform3f)
            IMP_SCRIPT_METHOD(Context,uniform3fv)
            IMP_SCRIPT_METHOD(Context,uniform3i)
            IMP_SCRIPT_METHOD(Context,uniform3iv)
            IMP_SCRIPT_METHOD(Context,uniform4f)
            IMP_SCRIPT_METHOD(Context,uniform4fv)
            IMP_SCRIPT_METHOD(Context,uniform4i)
            IMP_SCRIPT_METHOD(Context,uniform4iv)
            
            IMP_SCRIPT_METHOD(Context,uniformMatrix2fv)
            IMP_SCRIPT_METHOD(Context,uniformMatrix3fv)
            IMP_SCRIPT_METHOD(Context,uniformMatrix4fv)
            
            IMP_SCRIPT_METHOD(Context,useProgram)
            IMP_SCRIPT_METHOD(Context,validateProgram)
            
            IMP_SCRIPT_METHOD(Context,vertexAttrib1f)
            IMP_SCRIPT_METHOD(Context,vertexAttrib1fv)
            IMP_SCRIPT_METHOD(Context,vertexAttrib2f)
            IMP_SCRIPT_METHOD(Context,vertexAttrib2fv)
            IMP_SCRIPT_METHOD(Context,vertexAttrib3f)
            IMP_SCRIPT_METHOD(Context,vertexAttrib3fv)
            IMP_SCRIPT_METHOD(Context,vertexAttrib4f)
            IMP_SCRIPT_METHOD(Context,vertexAttrib4fv)
            IMP_SCRIPT_METHOD(Context,vertexAttribPointer)
            
            IMP_SCRIPT_METHOD(Context,viewport)

        };
        
        kk::script::SetMethod(ctx, -1, methods, sizeof(methods) / sizeof(kk::script::Method));
        
        
        IMP_SCRIPT_CLASS_END
        
        duk_ret_t Context::duk_drawingBufferWidth(duk_context * ctx) {
            duk_push_uint(ctx, _width);
            return 0;
        }
        
        duk_ret_t Context::duk_drawingBufferHeight(duk_context * ctx) {
            duk_push_uint(ctx, _height);
            return 0;
        }
        
        duk_ret_t Context::duk_activeTexture(duk_context * ctx) {
            glActiveTexture(kk::script::toUintArgument(ctx, 0, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_attachShader(duk_context * ctx) {
            //@TODO IMP
            return 0;
        }
        
        duk_ret_t Context::duk_bindAttribLocation(duk_context * ctx) {
            //@TODO IMP
            return 0;
        }
        
        duk_ret_t Context::duk_bindBuffer(duk_context * ctx) {
            //@TODO IMP
            return 0;
        }
        
        duk_ret_t Context::duk_bindFramebuffer(duk_context * ctx) {
            //@TODO IMP
            return 0;
        }
        
        duk_ret_t Context::duk_bindRenderbuffer(duk_context * ctx) { return 0; }
        
        duk_ret_t Context::duk_bindTexture(duk_context * ctx) { return 0; }
        
        duk_ret_t Context::duk_blendColor(duk_context * ctx) {
            glBlendColor(kk::script::toDoubleArgument(ctx, 0, 0),
                         kk::script::toDoubleArgument(ctx, 1, 0),
                         kk::script::toDoubleArgument(ctx, 2, 0),
                         kk::script::toDoubleArgument(ctx, 3, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_blendEquation(duk_context * ctx) {
            glBlendEquation(kk::script::toUintArgument(ctx, 0,0 ));
            return 0;
        }
        
        duk_ret_t Context::duk_blendEquationSeparate(duk_context * ctx) {
            glBlendEquationSeparate(kk::script::toUintArgument(ctx, 0,0 ),
                                    kk::script::toUintArgument(ctx, 1,0 ));
            return 0;
        }
        
        duk_ret_t Context::duk_blendFunc(duk_context * ctx) {
            glBlendFunc(kk::script::toUintArgument(ctx, 0,0 ),
                        kk::script::toUintArgument(ctx, 1,0 ));
            return 0;
        }
        
        duk_ret_t Context::duk_blendFuncSeparate(duk_context * ctx) {
            glBlendFuncSeparate(kk::script::toUintArgument(ctx, 0,0 ),
                                kk::script::toUintArgument(ctx, 1,0 ),
                                kk::script::toUintArgument(ctx, 2,0 ),
                                kk::script::toUintArgument(ctx, 3,0 ));
            return 0;
        }
        
        duk_ret_t Context::duk_bufferData(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 2) {
                
                size_t n = 0;
                void * data = nullptr;
                
                if(duk_is_buffer(ctx, -top + 1)) {
                    data = duk_to_buffer(ctx, -top + 1, &n);
                } else if(duk_is_buffer_data(ctx, -top + 1)) {
                    data = duk_get_buffer_data(ctx, -top + 1, &n);
                }
                
                if(data && n > 0) {
                    glBufferData(kk::script::toUintArgument(ctx, 0,0 ),
                                 n,
                                 data,
                                 kk::script::toUintArgument(ctx, 2,0 ));
                }
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_bufferSubData(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 2) {
                
                size_t n = 0;
                void * data = nullptr;
                
                if(duk_is_buffer(ctx, -top + 2)) {
                    data = duk_to_buffer(ctx, -top + 2, &n);
                } else if(duk_is_buffer_data(ctx, -top + 2)) {
                    data = duk_get_buffer_data(ctx, -top + 2, &n);
                }
                
                if(data && n > 0) {
                    glBufferSubData(kk::script::toUintArgument(ctx, 0,0 ),
                                    kk::script::toUintArgument(ctx, 1,0 ),
                                    n,
                                    data);
                }
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_checkFramebufferStatus(duk_context * ctx) {
            GLenum v = glCheckFramebufferStatus(kk::script::toUintArgument(ctx, 0,0 ));
            duk_push_uint(ctx, v);
            return 1;
        }
        
        duk_ret_t Context::duk_clear(duk_context * ctx) {
            glClear(kk::script::toUintArgument(ctx, 0,0 ));
            return 0;
        }
        
        duk_ret_t Context::duk_clearColor(duk_context * ctx) {
            glClearColor(kk::script::toDoubleArgument(ctx, 0,0 ),
                         kk::script::toDoubleArgument(ctx, 1,0 ),
                         kk::script::toDoubleArgument(ctx, 2,0 ),
                         kk::script::toDoubleArgument(ctx, 3,0 ));
            return 0;
        }
        
        duk_ret_t Context::duk_clearDepth(duk_context * ctx) {
            glClearDepthf(kk::script::toDoubleArgument(ctx, 0,0 ));
            return 0;
        }
        
        duk_ret_t Context::duk_clearStencil(duk_context * ctx) {
            glClearStencil(kk::script::toIntArgument(ctx, 0,0 ));
            return 0;
        }
        
        duk_ret_t Context::duk_colorMask(duk_context * ctx) {
            glColorMask(kk::script::toBooleanArgument(ctx, 0,false),
                        kk::script::toBooleanArgument(ctx, 1,false),
                        kk::script::toBooleanArgument(ctx, 2,false),
                        kk::script::toBooleanArgument(ctx, 3,false));
            return 0;
        }
        
        duk_ret_t Context::duk_compileShader(duk_context * ctx) { return 0; }
        duk_ret_t Context::duk_compressedTexImage2D(duk_context * ctx) { return 0; }
        duk_ret_t Context::duk_compressedTexSubImage2D(duk_context * ctx) { return 0; }
        duk_ret_t Context::duk_copyTexImage2D(duk_context * ctx) { return 0; }
        duk_ret_t Context::duk_copyTexSubImage2D(duk_context * ctx) { return 0; }
        
        duk_ret_t Context::duk_createBuffer(duk_context * ctx) {
            GLuint v = 0;
            glGenBuffers(1, &v);
            kk::script::PushObject(ctx, new Buffer(v));
            return 1;
        }
        
        duk_ret_t Context::duk_createFramebuffer(duk_context * ctx) {
            GLuint v = 0;
            glGenFramebuffers(1, &v);
            kk::script::PushObject(ctx, new Framebuffer(v));
            return 1;
        }
        duk_ret_t Context::duk_createProgram(duk_context * ctx) {
            GLuint v = glCreateProgram();
            kk::script::PushObject(ctx, new Program(v));
            return 1;
        }
        duk_ret_t Context::duk_createRenderbuffer(duk_context * ctx) {
            GLuint v = 0;
            glGenRenderbuffers(1, &v);
            kk::script::PushObject(ctx, new Renderbuffer(v));
            return 1;
        }
        duk_ret_t Context::duk_createShader(duk_context * ctx) {
            GLuint v = glCreateShader(kk::script::toUintArgument(ctx, 0, GL_VERTEX_SHADER));
            kk::script::PushObject(ctx, new Shader(v));
            return 1;
        }
        
        duk_ret_t Context::duk_createTexture(duk_context * ctx) {
            GLuint v = 0;
            glGenTextures(1, &v);
            kk::script::PushObject(ctx, new Texture(v));
            return 1;
        }
        
        duk_ret_t Context::duk_cullFace(duk_context * ctx) {
            glCullFace(kk::script::toUintArgument(ctx, 0, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_deleteBuffer(duk_context * ctx) {
            Buffer * v = dynamic_cast<Buffer *>(kk::script::toObjectArgument(ctx,0));
            if(v != nullptr) {
                GLuint i = v->value();
                glDeleteBuffers(1, &i);
            }
            return 0;
        }
        
        duk_ret_t Context::duk_deleteFramebuffer(duk_context * ctx) {
            
            Framebuffer * v = dynamic_cast<Framebuffer *>(kk::script::toObjectArgument(ctx,0));
            if(v != nullptr) {
                GLuint i = v->value();
                glDeleteFramebuffers(1, &i);
            }
            return 0;
        }
        
        duk_ret_t Context::duk_deleteProgram(duk_context * ctx) {
            Program * v = dynamic_cast<Program *>(kk::script::toObjectArgument(ctx,0));
            if(v != nullptr) {
                glDeleteProgram(v->value());
            }
            return 0;
        }
        
        duk_ret_t Context::duk_deleteRenderbuffer(duk_context * ctx) {
            Renderbuffer * v = dynamic_cast<Renderbuffer *>(kk::script::toObjectArgument(ctx,0));
            if(v != nullptr) {
                GLuint i = v->value();
                glDeleteRenderbuffers(1, &i);
            }
            return 0;
        }
        
        duk_ret_t Context::duk_deleteShader(duk_context * ctx) {
            Shader * v = dynamic_cast<Shader *>(kk::script::toObjectArgument(ctx,0));
            if(v != nullptr) {
                glDeleteShader(v->value());
            }
            return 0;
        }
        
        duk_ret_t Context::duk_deleteTexture(duk_context * ctx) {
            Texture * v = dynamic_cast<Texture *>(kk::script::toObjectArgument(ctx,0));
            if(v != nullptr) {
                GLuint i = v->value();
                glDeleteTextures(1, &i);
            }
            return 0;
        }
        
        duk_ret_t Context::duk_depthFunc(duk_context * ctx) {
            glDepthFunc(kk::script::toUintArgument(ctx, 0, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_depthMask(duk_context * ctx) {
            glDepthMask(kk::script::toBooleanArgument(ctx, 0, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_depthRange(duk_context * ctx) {
            glDepthRangef(kk::script::toDoubleArgument(ctx, 0, 0),
                          kk::script::toDoubleArgument(ctx, 0, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_detachShader(duk_context * ctx) {
            Program * p = dynamic_cast<Program *>(kk::script::toObjectArgument(ctx, 0));
            Shader * s = dynamic_cast<Shader *>(kk::script::toObjectArgument(ctx, 1));
            if(p && s) {
                glDetachShader(p->value(), s->value());
            }
            return 0;
        }
        
        duk_ret_t Context::duk_disable(duk_context * ctx) {
            glDisable(kk::script::toUintArgument(ctx, 0, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_disableVertexAttribArray(duk_context * ctx) {
            glDisableVertexAttribArray(kk::script::toUintArgument(ctx, 0, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_drawArrays(duk_context * ctx) {
            glDrawArrays(kk::script::toUintArgument(ctx, 0, 0),
                         kk::script::toIntArgument(ctx, 1, 0),
                         kk::script::toUintArgument(ctx, 2, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_drawElements(duk_context * ctx) {
            glDrawElements(kk::script::toUintArgument(ctx, 0, 0),
                           kk::script::toUintArgument(ctx, 1, 0),
                           kk::script::toUintArgument(ctx, 2, 0),
                           (void *)(long)kk::script::toUintArgument(ctx, 3, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_enable(duk_context * ctx) {
            glEnable(kk::script::toUintArgument(ctx, 0, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_enableVertexAttribArray(duk_context * ctx) {
            glEnableVertexAttribArray(kk::script::toUintArgument(ctx, 0, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_finish(duk_context * ctx) {
            glFinish();
            return 0;
        }
        
        duk_ret_t Context::duk_flush(duk_context * ctx) {
            glFlush();
            return 0;
        }
        
        duk_ret_t Context::duk_framebufferRenderbuffer(duk_context * ctx) {
            Renderbuffer * v = dynamic_cast<Renderbuffer *>( kk::script::toObjectArgument(ctx, 3) );
            
            if(v) {
                glFramebufferRenderbuffer(kk::script::toUintArgument(ctx, 0, 0),
                                          kk::script::toUintArgument(ctx, 1, 0),
                                          kk::script::toUintArgument(ctx, 2, 0),
                                          v->value());
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_framebufferTexture2D(duk_context * ctx) {
            
            Texture * v = dynamic_cast<Texture *>( kk::script::toObjectArgument(ctx, 3) );
            
            if(v) {
                glFramebufferTexture2D(kk::script::toUintArgument(ctx, 0, 0),
                                       kk::script::toUintArgument(ctx, 1, 0),
                                       kk::script::toUintArgument(ctx, 2, 0),
                                       v->value(),
                                       kk::script::toIntArgument(ctx, 4, 0));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_frontFace(duk_context * ctx) {
            glFrontFace(kk::script::toUintArgument(ctx, 0, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_generateMipmap(duk_context * ctx) {
            glGenerateMipmap(kk::script::toUintArgument(ctx, 0, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_getActiveAttrib(duk_context * ctx) {
            
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                
                GLsizei length = 0;
                GLint size = 0;
                GLenum type = 0;
                GLchar name[256] = "";
                
                glGetActiveAttrib(v->value(),
                                  kk::script::toUintArgument(ctx, 1, 0),
                                  sizeof(name) - 1,
                                  &length,
                                  &size,
                                  &type,
                                  name);
                
                duk_push_object(ctx);
            
                duk_push_uint(ctx, length);
                duk_put_prop_string(ctx, -2, "length");
                
                duk_push_int(ctx, size);
                duk_put_prop_string(ctx, -2, "size");
                
                duk_push_uint(ctx, type);
                duk_put_prop_string(ctx, -2, "type");
                
                duk_push_string(ctx, name);
                duk_put_prop_string(ctx, -2, "name");
                
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getActiveUniform(duk_context * ctx) {
            
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                
                GLsizei length = 0;
                GLint size = 0;
                GLenum type = 0;
                GLchar name[256] = "";
                
                glGetActiveUniform(v->value(),
                                  kk::script::toUintArgument(ctx, 1, 0),
                                  sizeof(name) - 1,
                                  &length,
                                  &size,
                                  &type,
                                  name);
                
                duk_push_object(ctx);
                
                duk_push_uint(ctx, length);
                duk_put_prop_string(ctx, -2, "length");
                
                duk_push_int(ctx, size);
                duk_put_prop_string(ctx, -2, "size");
                
                duk_push_uint(ctx, type);
                duk_put_prop_string(ctx, -2, "type");
                
                duk_push_string(ctx, name);
                duk_put_prop_string(ctx, -2, "name");
                
                return 1;
            }
            
            return 0;
            
        }
        
        duk_ret_t Context::duk_getAttachedShaders(duk_context * ctx) {
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                
                GLuint vs[64];
                GLsizei n = 0;
                
                glGetAttachedShaders(v->value(), 64, &n, vs);
                
                duk_push_array(ctx);
                
                for(duk_uarridx_t i =0;i<n;i++) {
                    kk::script::PushObject(ctx, new Shader(vs[i]));
                    duk_put_prop_index(ctx, -2, i);
                }
                
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getAttribLocation(duk_context * ctx) {
            
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                GLint i = glGetAttribLocation(v->value(), kk::script::toStringArgument(ctx, 1, "").c_str());
                duk_push_int(ctx, i);
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getBufferParameter(duk_context * ctx) {
            GLint v = 0;
            glGetBufferParameteriv(kk::script::toUintArgument(ctx, 0, 0),
                                   kk::script::toUintArgument(ctx, 1, 0),
                                   &v);
            duk_push_int(ctx, v);
            return 1;
        }
        
        duk_ret_t Context::duk_getParameter(duk_context * ctx) {
            return 0;
        }
        
        duk_ret_t Context::duk_getError(duk_context * ctx) {
            GLenum v = glGetError();
            duk_push_uint(ctx, v);
            return 1;
        }
        
        duk_ret_t Context::duk_getFramebufferAttachmentParameter(duk_context * ctx) {
            
            GLint v = 0;
            glGetFramebufferAttachmentParameteriv(kk::script::toUintArgument(ctx, 0, 0),
                                                  kk::script::toUintArgument(ctx, 1, 0),
                                                  kk::script::toUintArgument(ctx, 2, 0),
                                                  &v);
            
            duk_push_int(ctx, v);
            
            return 1;
        }
        
        duk_ret_t Context::duk_getProgramParameter(duk_context * ctx) {
            
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                GLint i = 0;
                glGetProgramiv(v->value(), kk::script::toUintArgument(ctx, 1, 0), &i);
                duk_push_int(ctx, i);
                return 1;
            }
            
            return 0;
            
        }
        
        duk_ret_t Context::duk_getProgramInfoLog(duk_context * ctx) {
            
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                GLsizei n =0;
                char data[2048] = "";
                glGetProgramInfoLog(v->value(), sizeof(data), &n, data);
                duk_push_lstring(ctx, data, n);
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getRenderbufferParameter(duk_context * ctx) {
            GLint v = 0;
            glGetRenderbufferParameteriv(kk::script::toUintArgument(ctx, 0, 0),
                                         kk::script::toUintArgument(ctx, 1, 0),
                                         &v);
            
            duk_push_int(ctx, v);
            
            return 1;
        }
        
        duk_ret_t Context::duk_getShaderParameter(duk_context * ctx) {
            
            Shader * v = dynamic_cast<Shader *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                GLint i = 0;
                glGetShaderiv(v->value(), kk::script::toUintArgument(ctx, 1, 0), &i);
                duk_push_int(ctx, i);
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getShaderPrecisionFormat(duk_context * ctx) {
            GLint range = 0;
            GLint precision = 0;
            glGetShaderPrecisionFormat(kk::script::toUintArgument(ctx, 0, 0),
                                       kk::script::toUintArgument(ctx, 1, 0),
                                       &range,
                                       &precision);
            duk_push_object(ctx);
            duk_push_int(ctx, 0);
            duk_put_prop_string(ctx, -2, "rangeMin");
            
            duk_push_int(ctx, range);
            duk_put_prop_string(ctx, -2, "rangeMax");
            
            duk_push_int(ctx, precision);
            duk_put_prop_string(ctx, -2, "precision");

            return 0;
        }
        
        duk_ret_t Context::duk_getShaderInfoLog(duk_context * ctx) {
            
            Shader * v = dynamic_cast<Shader *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                char data[2048];
                GLsizei n = 0;
                glGetShaderInfoLog(v->value(), sizeof(data), &n, data);
                duk_push_lstring(ctx, data, n);
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getShaderSource(duk_context * ctx) {
            
            Shader * v = dynamic_cast<Shader *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                char data[20480];
                GLsizei n = 0;
                glGetShaderSource(v->value(), sizeof(data), &n, data);
                duk_push_lstring(ctx, data, n);
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getTexParameter(duk_context * ctx) {
            
            GLint i = 0;
            
            glGetTexParameteriv(kk::script::toUintArgument(ctx, 0, 0),
                                kk::script::toUintArgument(ctx, 1, 0), &i);
            
            duk_push_int(ctx, i);
    
            return 1;
        }
        
        duk_ret_t Context::duk_getUniform(duk_context * ctx) {
            
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                GLint i = 0;
                glGetUniformiv(v->value(),
                               kk::script::toIntArgument(ctx, 1, 0),
                               &i);
                duk_push_int(ctx, i);
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getUniformLocation(duk_context * ctx) {
            
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                
                int i = glGetUniformLocation(v->value(), kk::script::toStringArgument(ctx, 1, "").c_str());
                
                duk_push_int(ctx, i);
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getVertexAttrib(duk_context * ctx) {
            
            GLint i = 0;
            
            glGetVertexAttribiv(kk::script::toUintArgument(ctx, 0, 0),
                                kk::script::toUintArgument(ctx, 1, 0), &i);
            
            duk_push_int(ctx, i);
            return 1;
        }
        
        duk_ret_t Context::duk_getVertexAttribOffset(duk_context * ctx) {
            
            return 0;
        }
        
        
        duk_ret_t Context::duk_hint(duk_context * ctx) {
            glHint(kk::script::toUintArgument(ctx, 0, 0),
                   kk::script::toUintArgument(ctx, 1, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_isBuffer(duk_context * ctx) {
            Buffer * v = dynamic_cast<Buffer *>( kk::script::toObjectArgument(ctx, 0) );
            duk_push_boolean(ctx, v != nullptr && glIsBuffer(v->value()));
            return 1;
        }
        
        duk_ret_t Context::duk_isEnabled(duk_context * ctx) {
            glIsEnabled(kk::script::toUintArgument(ctx, 0, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_isFramebuffer(duk_context * ctx) {
            Framebuffer * v = dynamic_cast<Framebuffer *>( kk::script::toObjectArgument(ctx, 0) );
            duk_push_boolean(ctx, v != nullptr && glIsFramebuffer(v->value()));
            return 1;
        }
        
        duk_ret_t Context::duk_isProgram(duk_context * ctx) {
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            duk_push_boolean(ctx, v != nullptr && glIsProgram(v->value()));
            return 1;
        }
        
        duk_ret_t Context::duk_isRenderbuffer(duk_context * ctx) {
            Renderbuffer * v = dynamic_cast<Renderbuffer *>( kk::script::toObjectArgument(ctx, 0) );
            duk_push_boolean(ctx, v != nullptr && glIsRenderbuffer(v->value()));
            return 1;
        }
        
        duk_ret_t Context::duk_isShader(duk_context * ctx) {
            Shader * v = dynamic_cast<Shader *>( kk::script::toObjectArgument(ctx, 0) );
            duk_push_boolean(ctx, v != nullptr && glIsShader(v->value()));
            return 1;
        }
        
        duk_ret_t Context::duk_isTexture(duk_context * ctx) {
            Texture * v = dynamic_cast<Texture *>( kk::script::toObjectArgument(ctx, 0) );
            duk_push_boolean(ctx, v != nullptr && glIsTexture(v->value()));
            return 1;
        }
        
        duk_ret_t Context::duk_lineWidth(duk_context * ctx) {
            glLineWidth(kk::script::toDoubleArgument(ctx, 0, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_linkProgram(duk_context * ctx) {
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            if(v != nullptr) {
                glLinkProgram(v->value());
            }
            return 0;
        }
        
        duk_ret_t Context::duk_pixelStorei(duk_context * ctx) {
            glPixelStorei(kk::script::toUintArgument(ctx, 0, 0),
                          kk::script::toIntArgument(ctx, 1, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_polygonOffset(duk_context * ctx) {
            glPolygonOffset(kk::script::toDoubleArgument(ctx, 0, 0),
                            kk::script::toDoubleArgument(ctx, 1, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_readPixels(duk_context * ctx) {
            
            
            return 0;
        }
        
        duk_ret_t Context::duk_renderbufferStorage(duk_context * ctx) { return 0; }
        duk_ret_t Context::duk_sampleCoverage(duk_context * ctx) { return 0; }
        duk_ret_t Context::duk_scissor(duk_context * ctx) { return 0; }
        
        duk_ret_t Context::duk_shaderSource(duk_context * ctx) { return 0; }
        
        duk_ret_t Context::duk_stencilFunc(duk_context * ctx) { return 0; }
        duk_ret_t Context::duk_stencilFuncSeparate(duk_context * ctx) { return 0; }
        duk_ret_t Context::duk_stencilMask(duk_context * ctx) { return 0; }
        duk_ret_t Context::duk_stencilMaskSeparate(duk_context * ctx) { return 0; }
        duk_ret_t Context::duk_stencilOp(duk_context * ctx) { return 0; }
        duk_ret_t Context::duk_stencilOpSeparate(duk_context * ctx) { return 0; }
        
        duk_ret_t Context::duk_texImage2D(duk_context * ctx) { return 0; }
        
        duk_ret_t Context::duk_texParameterf(duk_context * ctx) { return 0; }
        duk_ret_t Context::duk_texParameteri(duk_context * ctx) { return 0; }
        
        duk_ret_t Context::duk_texSubImage2D(duk_context * ctx) { return 0; }
        
        duk_ret_t Context::duk_uniform1f(duk_context * ctx) {
            glUniform1f(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toDoubleArgument(ctx, 1, 0));
            return 0;
        }
        duk_ret_t Context::duk_uniform1fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform1fv(kk::script::toUintArgument(ctx, 0, 0),
                             (GLsizei) (n / sizeof(GLfloat)),
                             (GLfloat *) data);
            }
            return 0;
        }
        duk_ret_t Context::duk_uniform1i(duk_context * ctx) {
            glUniform1i(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toIntArgument(ctx, 1, 0));
            return 0;
        }
        duk_ret_t Context::duk_uniform1iv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform1iv(kk::script::toUintArgument(ctx, 0, 0),
                             (GLsizei) (n / sizeof(GLint)),
                             (GLint *) data);
            }
            return 0;
        }
        duk_ret_t Context::duk_uniform2f(duk_context * ctx) {
            glUniform2f(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toDoubleArgument(ctx, 1, 0),
                        kk::script::toDoubleArgument(ctx, 2, 0));
            return 0;
        }
        duk_ret_t Context::duk_uniform2fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform2fv(kk::script::toUintArgument(ctx, 0, 0),
                             (GLsizei) (n / sizeof(GLfloat)),
                             (GLfloat *) data);
            }
            return 0;
        }
        duk_ret_t Context::duk_uniform2i(duk_context * ctx) {
            glUniform2i(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toIntArgument(ctx, 1, 0),
                        kk::script::toIntArgument(ctx, 2, 0));
            return 0;
        }
        duk_ret_t Context::duk_uniform2iv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform2iv(kk::script::toUintArgument(ctx, 0, 0),
                             (GLsizei) (n / sizeof(GLint)),
                             (GLint *) data);
            }
            return 0;
        }
        duk_ret_t Context::duk_uniform3f(duk_context * ctx) {
            glUniform3f(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toDoubleArgument(ctx, 1, 0),
                        kk::script::toDoubleArgument(ctx, 2, 0),
                        kk::script::toDoubleArgument(ctx, 3, 0));
            return 0;
        }
        duk_ret_t Context::duk_uniform3fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform3fv(kk::script::toUintArgument(ctx, 0, 0),
                             (GLsizei) (n / sizeof(GLfloat)),
                             (GLfloat *) data);
            }
            return 0;
        }
        duk_ret_t Context::duk_uniform3i(duk_context * ctx) {
            glUniform3i(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toIntArgument(ctx, 1, 0),
                        kk::script::toIntArgument(ctx, 2, 0),
                        kk::script::toIntArgument(ctx, 3, 0));
            return 0;
        }
        duk_ret_t Context::duk_uniform3iv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform3iv(kk::script::toUintArgument(ctx, 0, 0),
                             (GLsizei) (n / sizeof(GLint)),
                             (GLint *) data);
            }
            return 0;
        }
        duk_ret_t Context::duk_uniform4f(duk_context * ctx) {
            glUniform4f(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toDoubleArgument(ctx, 1, 0),
                        kk::script::toDoubleArgument(ctx, 2, 0),
                        kk::script::toDoubleArgument(ctx, 3, 0),
                        kk::script::toDoubleArgument(ctx, 4, 0));
            return 0;
        }
        duk_ret_t Context::duk_uniform4fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform4fv(kk::script::toUintArgument(ctx, 0, 0),
                             (GLsizei) (n / sizeof(GLfloat)),
                             (GLfloat *) data);
            }
            return 0;
        }
        duk_ret_t Context::duk_uniform4i(duk_context * ctx) {
            glUniform4i(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toIntArgument(ctx, 1, 0),
                        kk::script::toIntArgument(ctx, 2, 0),
                        kk::script::toIntArgument(ctx, 3, 0),
                        kk::script::toIntArgument(ctx, 4, 0));
            return 0;
        }
        duk_ret_t Context::duk_uniform4iv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform4iv(kk::script::toUintArgument(ctx, 0, 0),
                                   (GLsizei) (n / sizeof(GLint)),
                                   (GLint *) data);
            }
            return 0;
        }
        
        duk_ret_t Context::duk_uniformMatrix2fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 2 && duk_is_buffer_data(ctx, -top + 2)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 2, &n);
                glUniformMatrix2fv(kk::script::toUintArgument(ctx, 0, 0),
                                   (GLsizei) (n / sizeof(GLfloat)),
                                   kk::script::toBooleanArgument(ctx, 1, 0),
                                   (GLfloat *) data);
            }
            return 0;
        }
        duk_ret_t Context::duk_uniformMatrix3fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 2 && duk_is_buffer_data(ctx, -top + 2)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 2, &n);
                glUniformMatrix3fv(kk::script::toUintArgument(ctx, 0, 0),
                                   (GLsizei) (n / sizeof(GLfloat)),
                                   kk::script::toBooleanArgument(ctx, 1, 0),
                                   (GLfloat *) data);
            }
            return 0;
        }
        duk_ret_t Context::duk_uniformMatrix4fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 2 && duk_is_buffer_data(ctx, -top + 2)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 2, &n);
                glUniformMatrix4fv(kk::script::toUintArgument(ctx, 0, 0),
                                   (GLsizei) (n / sizeof(GLfloat)),
                                   kk::script::toBooleanArgument(ctx, 1, 0),
                                   (GLfloat *) data);
            }
            return 0;
        }
        
        duk_ret_t Context::duk_useProgram(duk_context * ctx) { return 0; }
        duk_ret_t Context::duk_validateProgram(duk_context * ctx) { return 0; }
        
        duk_ret_t Context::duk_vertexAttrib1f(duk_context * ctx) {
            glVertexAttrib1f(kk::script::toUintArgument(ctx, 0, 0),
                             kk::script::toDoubleArgument(ctx, 1, 0));
            return 0;
        }
        duk_ret_t Context::duk_vertexAttrib1fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glVertexAttrib1fv(kk::script::toUintArgument(ctx, 0, 0), (GLfloat *) data);
            }
            return 0;
        }
        duk_ret_t Context::duk_vertexAttrib2f(duk_context * ctx) {
            glVertexAttrib2f(kk::script::toUintArgument(ctx, 0, 0),
                             kk::script::toDoubleArgument(ctx, 1, 0),
                             kk::script::toDoubleArgument(ctx, 2, 0));
            return 0;
        }
        duk_ret_t Context::duk_vertexAttrib2fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glVertexAttrib2fv(kk::script::toUintArgument(ctx, 0, 0), (GLfloat *) data);
            }
            return 0;
        }
        duk_ret_t Context::duk_vertexAttrib3f(duk_context * ctx) {
            glVertexAttrib3f(kk::script::toUintArgument(ctx, 0, 0),
                             kk::script::toDoubleArgument(ctx, 1, 0),
                             kk::script::toDoubleArgument(ctx, 2, 0),
                             kk::script::toDoubleArgument(ctx, 3, 0));
            return 0;
        }
        duk_ret_t Context::duk_vertexAttrib3fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glVertexAttrib3fv(kk::script::toUintArgument(ctx, 0, 0), (GLfloat *) data);
            }
            return 0;
        }
        duk_ret_t Context::duk_vertexAttrib4f(duk_context * ctx) {
            glVertexAttrib4f(kk::script::toUintArgument(ctx, 0, 0),
                             kk::script::toDoubleArgument(ctx, 1, 0),
                             kk::script::toDoubleArgument(ctx, 2, 0),
                             kk::script::toDoubleArgument(ctx, 3, 0),
                             kk::script::toDoubleArgument(ctx, 4, 0));
            return 0;
        }
        duk_ret_t Context::duk_vertexAttrib4fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glVertexAttrib4fv(kk::script::toUintArgument(ctx, 0, 0), (GLfloat *) data);
            }
            return 0;
        }
        duk_ret_t Context::duk_vertexAttribPointer(duk_context * ctx) {
            glVertexAttribPointer(kk::script::toUintArgument(ctx, 0, 0),
                                  kk::script::toIntArgument(ctx, 0, 0),
                                  kk::script::toUintArgument(ctx, 0, 0),
                                  kk::script::toBooleanArgument(ctx, 0, 0),
                                  kk::script::toUintArgument(ctx, 0, 0),
                                  (void *) (long) kk::script::toIntArgument(ctx, 0, 0));
            return 0;
        }
        
        duk_ret_t Context::duk_viewport(duk_context * ctx) {
            glViewport(kk::script::toIntArgument(ctx, 0, 0), kk::script::toIntArgument(ctx, 0, 0), kk::script::toUintArgument(ctx, 0, 0), kk::script::toUintArgument(ctx, 0, 0));
            return 0;
        }
        
    }
    
}
