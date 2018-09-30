//
//  WebGLContextJS.cc
//  KKCanvas
//
//  Created by zhanghailong on 2018/9/28.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "WebGLContext.h"
#include "CGContext.h"

#define GL_DEPTH_STENCIL 0x84F9
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A

namespace kk {
    
    
    namespace WebGL {
        
#ifdef DEBUG
#define KK_GL_ERROR(ctx) for(GLenum v = glGetError(); v !=0; v = 0) { kk::Log("[WebGL] [ERROR] %s(%d) %s: %x",__FILE__,__LINE__,__FUNCTION__,v); duk_push_context_dump(ctx); return duk_push_error_object(ctx,DUK_ERR_ERROR,"[WebGL] [ERROR] %x",v); } kk::Log("[WebGL] %s",__FUNCTION__);
#else
#define KK_GL_ERROR(ctx)
#endif
        
        
        IMP_SCRIPT_CLASS_BEGIN_NOALLOC(nullptr, Context, WebGLContext)
        
        IMP_SCRIPT_CONST_UINT(TRUE               , GL_TRUE)
        IMP_SCRIPT_CONST_UINT(FALSE              , GL_FALSE)
        
        /* ClearBufferMask */
        IMP_SCRIPT_CONST_UINT(DEPTH_BUFFER_BIT               , GL_DEPTH_BUFFER_BIT)
        IMP_SCRIPT_CONST_UINT(STENCIL_BUFFER_BIT             , GL_STENCIL_BUFFER_BIT)
        IMP_SCRIPT_CONST_UINT(COLOR_BUFFER_BIT               , GL_COLOR_BUFFER_BIT)
        
        /* BeginMode */
        IMP_SCRIPT_CONST_UINT(POINTS                         , GL_POINTS)
        IMP_SCRIPT_CONST_UINT(LINES                          , GL_LINES)
        IMP_SCRIPT_CONST_UINT(LINE_LOOP                      , GL_LINE_LOOP)
        IMP_SCRIPT_CONST_UINT(LINE_STRIP                     , GL_LINE_STRIP)
        IMP_SCRIPT_CONST_UINT(TRIANGLES                      , GL_TRIANGLES)
        IMP_SCRIPT_CONST_UINT(TRIANGLE_STRIP                 , GL_TRIANGLE_STRIP)
        IMP_SCRIPT_CONST_UINT(TRIANGLE_FAN                   , GL_TRIANGLE_FAN)
        
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
        IMP_SCRIPT_CONST_UINT(ZERO                           , GL_ZERO)
        IMP_SCRIPT_CONST_UINT(ONE                            , GL_ONE)
        IMP_SCRIPT_CONST_UINT(SRC_COLOR                      , GL_SRC_COLOR)
        IMP_SCRIPT_CONST_UINT(ONE_MINUS_SRC_COLOR            , GL_ONE_MINUS_SRC_COLOR)
        IMP_SCRIPT_CONST_UINT(SRC_ALPHA                      , GL_SRC_ALPHA)
        IMP_SCRIPT_CONST_UINT(ONE_MINUS_SRC_ALPHA            , GL_ONE_MINUS_SRC_ALPHA)
        IMP_SCRIPT_CONST_UINT(DST_ALPHA                      , GL_DST_ALPHA)
        IMP_SCRIPT_CONST_UINT(ONE_MINUS_DST_ALPHA            , GL_ONE_MINUS_DST_ALPHA)
        
        /* BlendingFactorSrc */
        /*      ZERO */
        /*      ONE */
        IMP_SCRIPT_CONST_UINT(DST_COLOR                      , GL_DST_COLOR)
        IMP_SCRIPT_CONST_UINT(ONE_MINUS_DST_COLOR            , GL_ONE_MINUS_DST_COLOR)
        IMP_SCRIPT_CONST_UINT(SRC_ALPHA_SATURATE             , GL_SRC_ALPHA_SATURATE)
        /*      SRC_ALPHA */
        /*      ONE_MINUS_SRC_ALPHA */
        /*      DST_ALPHA */
        /*      ONE_MINUS_DST_ALPHA */
        
        /* BlendEquationSeparate */
        IMP_SCRIPT_CONST_UINT(FUNC_ADD                       , GL_FUNC_ADD)
        IMP_SCRIPT_CONST_UINT(BLEND_EQUATION                 , GL_BLEND_EQUATION)
        IMP_SCRIPT_CONST_UINT(BLEND_EQUATION_RGB             , GL_BLEND_EQUATION_RGB)   /* same as BLEND_EQUATION */
        IMP_SCRIPT_CONST_UINT(BLEND_EQUATION_ALPHA           , GL_BLEND_EQUATION_ALPHA)
        
        /* BlendSubtract */
        IMP_SCRIPT_CONST_UINT(FUNC_SUBTRACT                  , GL_FUNC_SUBTRACT)
        IMP_SCRIPT_CONST_UINT(FUNC_REVERSE_SUBTRACT          , GL_FUNC_REVERSE_SUBTRACT)
        
        /* Separate Blend Functions */
        IMP_SCRIPT_CONST_UINT(BLEND_DST_RGB                  , GL_BLEND_DST_RGB)
        IMP_SCRIPT_CONST_UINT(BLEND_SRC_RGB                  , GL_BLEND_SRC_RGB)
        IMP_SCRIPT_CONST_UINT(BLEND_DST_ALPHA                , GL_BLEND_DST_ALPHA)
        IMP_SCRIPT_CONST_UINT(BLEND_SRC_ALPHA                , GL_BLEND_SRC_ALPHA)
        IMP_SCRIPT_CONST_UINT(CONSTANT_COLOR                 , GL_CONSTANT_COLOR)
        IMP_SCRIPT_CONST_UINT(ONE_MINUS_CONSTANT_COLOR       , GL_ONE_MINUS_CONSTANT_COLOR)
        IMP_SCRIPT_CONST_UINT(CONSTANT_ALPHA                 , GL_CONSTANT_ALPHA)
        IMP_SCRIPT_CONST_UINT(ONE_MINUS_CONSTANT_ALPHA       , GL_ONE_MINUS_CONSTANT_ALPHA)
        IMP_SCRIPT_CONST_UINT(BLEND_COLOR                    , GL_BLEND_COLOR)
        
        /* Buffer Objects */
        IMP_SCRIPT_CONST_UINT(ARRAY_BUFFER                   , GL_ARRAY_BUFFER)
        IMP_SCRIPT_CONST_UINT(ELEMENT_ARRAY_BUFFER           , GL_ELEMENT_ARRAY_BUFFER)
        IMP_SCRIPT_CONST_UINT(ARRAY_BUFFER_BINDING           , GL_ARRAY_BUFFER_BINDING)
        IMP_SCRIPT_CONST_UINT(ELEMENT_ARRAY_BUFFER_BINDING   , GL_ELEMENT_ARRAY_BUFFER_BINDING)
        
        IMP_SCRIPT_CONST_UINT(STREAM_DRAW                    , GL_STREAM_DRAW)
        IMP_SCRIPT_CONST_UINT(STATIC_DRAW                    , GL_STATIC_DRAW)
        IMP_SCRIPT_CONST_UINT(DYNAMIC_DRAW                   , GL_DYNAMIC_DRAW)
        
        IMP_SCRIPT_CONST_UINT(BUFFER_SIZE                    , GL_BUFFER_SIZE)
        IMP_SCRIPT_CONST_UINT(BUFFER_USAGE                   , GL_BUFFER_USAGE)
        
        IMP_SCRIPT_CONST_UINT(CURRENT_VERTEX_ATTRIB          , GL_CURRENT_VERTEX_ATTRIB)
        
        /* CullFaceMode */
        IMP_SCRIPT_CONST_UINT(FRONT                          , GL_FRONT)
        IMP_SCRIPT_CONST_UINT(BACK                           , GL_BACK)
        IMP_SCRIPT_CONST_UINT(FRONT_AND_BACK                 , GL_FRONT_AND_BACK)
        
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
        IMP_SCRIPT_CONST_UINT(CULL_FACE                      , GL_CULL_FACE)
        IMP_SCRIPT_CONST_UINT(BLEND                          , GL_BLEND)
        IMP_SCRIPT_CONST_UINT(DITHER                         , GL_DITHER)
        IMP_SCRIPT_CONST_UINT(STENCIL_TEST                   , GL_STENCIL_TEST)
        IMP_SCRIPT_CONST_UINT(DEPTH_TEST                     , GL_DEPTH_TEST)
        IMP_SCRIPT_CONST_UINT(SCISSOR_TEST                   , GL_SCISSOR_TEST)
        IMP_SCRIPT_CONST_UINT(POLYGON_OFFSET_FILL            , GL_POLYGON_OFFSET_FILL)
        IMP_SCRIPT_CONST_UINT(SAMPLE_ALPHA_TO_COVERAGE       , GL_SAMPLE_ALPHA_TO_COVERAGE)
        IMP_SCRIPT_CONST_UINT(SAMPLE_COVERAGE                , GL_SAMPLE_COVERAGE)
        
        /* ErrorCode */
        IMP_SCRIPT_CONST_UINT(NO_ERROR                       , GL_NO_ERROR)
        IMP_SCRIPT_CONST_UINT(INVALID_ENUM                   , GL_INVALID_ENUM)
        IMP_SCRIPT_CONST_UINT(INVALID_VALUE                  , GL_INVALID_VALUE)
        IMP_SCRIPT_CONST_UINT(INVALID_OPERATION              , GL_INVALID_OPERATION)
        IMP_SCRIPT_CONST_UINT(OUT_OF_MEMORY                  , GL_OUT_OF_MEMORY)
        
        /* FrontFaceDirection */
        IMP_SCRIPT_CONST_UINT(CW                             , GL_CW)
        IMP_SCRIPT_CONST_UINT(CCW                            , GL_CCW)
        
        
        /* GetPName */
        IMP_SCRIPT_CONST_UINT(LINE_WIDTH                     , GL_LINE_WIDTH)
        IMP_SCRIPT_CONST_UINT(ALIASED_POINT_SIZE_RANGE       , GL_ALIASED_POINT_SIZE_RANGE)
        IMP_SCRIPT_CONST_UINT(ALIASED_LINE_WIDTH_RANGE       , GL_ALIASED_LINE_WIDTH_RANGE)
        IMP_SCRIPT_CONST_UINT(CULL_FACE_MODE                 , GL_CULL_FACE_MODE)
        IMP_SCRIPT_CONST_UINT(FRONT_FACE                     , GL_FRONT_FACE)
        IMP_SCRIPT_CONST_UINT(DEPTH_RANGE                    , GL_DEPTH_RANGE)
        IMP_SCRIPT_CONST_UINT(DEPTH_WRITEMASK                , GL_DEPTH_WRITEMASK)
        IMP_SCRIPT_CONST_UINT(DEPTH_CLEAR_VALUE              , GL_DEPTH_CLEAR_VALUE)
        IMP_SCRIPT_CONST_UINT(DEPTH_FUNC                     , GL_DEPTH_FUNC)
        IMP_SCRIPT_CONST_UINT(STENCIL_CLEAR_VALUE            , GL_STENCIL_CLEAR_VALUE)
        IMP_SCRIPT_CONST_UINT(STENCIL_FUNC                   , GL_STENCIL_FUNC)
        IMP_SCRIPT_CONST_UINT(STENCIL_FAIL                   , GL_STENCIL_FAIL)
        IMP_SCRIPT_CONST_UINT(STENCIL_PASS_DEPTH_FAIL        , GL_STENCIL_PASS_DEPTH_FAIL)
        IMP_SCRIPT_CONST_UINT(STENCIL_PASS_DEPTH_PASS        , GL_STENCIL_PASS_DEPTH_PASS)
        IMP_SCRIPT_CONST_UINT(STENCIL_REF                    , GL_STENCIL_REF)
        IMP_SCRIPT_CONST_UINT(STENCIL_VALUE_MASK             , GL_STENCIL_VALUE_MASK)
        IMP_SCRIPT_CONST_UINT(STENCIL_WRITEMASK              , GL_STENCIL_WRITEMASK)
        IMP_SCRIPT_CONST_UINT(STENCIL_BACK_FUNC              , GL_STENCIL_BACK_FUNC)
        IMP_SCRIPT_CONST_UINT(STENCIL_BACK_FAIL              , GL_STENCIL_BACK_FAIL)
        IMP_SCRIPT_CONST_UINT(STENCIL_BACK_PASS_DEPTH_FAIL   , GL_STENCIL_BACK_PASS_DEPTH_FAIL)
        IMP_SCRIPT_CONST_UINT(STENCIL_BACK_PASS_DEPTH_PASS   , GL_STENCIL_BACK_PASS_DEPTH_PASS)
        IMP_SCRIPT_CONST_UINT(STENCIL_BACK_REF               , GL_STENCIL_BACK_REF)
        IMP_SCRIPT_CONST_UINT(STENCIL_BACK_VALUE_MASK        , GL_STENCIL_BACK_VALUE_MASK)
        IMP_SCRIPT_CONST_UINT(STENCIL_BACK_WRITEMASK         , GL_STENCIL_BACK_WRITEMASK)
        IMP_SCRIPT_CONST_UINT(VIEWPORT                       , GL_VIEWPORT)
        IMP_SCRIPT_CONST_UINT(SCISSOR_BOX                    , GL_SCISSOR_BOX)
        /*      SCISSOR_TEST */
        IMP_SCRIPT_CONST_UINT(COLOR_CLEAR_VALUE              , GL_COLOR_CLEAR_VALUE)
        IMP_SCRIPT_CONST_UINT(COLOR_WRITEMASK                , GL_COLOR_WRITEMASK)
        IMP_SCRIPT_CONST_UINT(UNPACK_ALIGNMENT               , GL_UNPACK_ALIGNMENT)
        IMP_SCRIPT_CONST_UINT(PACK_ALIGNMENT                 , GL_PACK_ALIGNMENT)
        IMP_SCRIPT_CONST_UINT(MAX_TEXTURE_SIZE               , GL_MAX_TEXTURE_SIZE)
        IMP_SCRIPT_CONST_UINT(MAX_VIEWPORT_DIMS              , GL_MAX_VIEWPORT_DIMS)
        IMP_SCRIPT_CONST_UINT(SUBPIXEL_BITS                  , GL_SUBPIXEL_BITS)
        IMP_SCRIPT_CONST_UINT(RED_BITS                       , GL_RED_BITS)
        IMP_SCRIPT_CONST_UINT(GREEN_BITS                     , GL_GREEN_BITS)
        IMP_SCRIPT_CONST_UINT(BLUE_BITS                      , GL_BLUE_BITS)
        IMP_SCRIPT_CONST_UINT(ALPHA_BITS                     , GL_ALPHA_BITS)
        IMP_SCRIPT_CONST_UINT(DEPTH_BITS                     , GL_DEPTH_BITS)
        IMP_SCRIPT_CONST_UINT(STENCIL_BITS                   , GL_STENCIL_BITS)
        IMP_SCRIPT_CONST_UINT(POLYGON_OFFSET_UNITS           , GL_POLYGON_OFFSET_UNITS)
        /*      POLYGON_OFFSET_FILL */
        IMP_SCRIPT_CONST_UINT(POLYGON_OFFSET_FACTOR          , GL_POLYGON_OFFSET_FACTOR)
        IMP_SCRIPT_CONST_UINT(TEXTURE_BINDING_2D             , GL_TEXTURE_BINDING_2D)
        IMP_SCRIPT_CONST_UINT(SAMPLE_BUFFERS                 , GL_SAMPLE_BUFFERS)
        IMP_SCRIPT_CONST_UINT(SAMPLES                        , GL_SAMPLES)
        IMP_SCRIPT_CONST_UINT(SAMPLE_COVERAGE_VALUE          , GL_SAMPLE_COVERAGE_VALUE)
        IMP_SCRIPT_CONST_UINT(SAMPLE_COVERAGE_INVERT         , GL_SAMPLE_COVERAGE_INVERT)
        
        /* GetTextureParameter */
        /*      TEXTURE_MAG_FILTER */
        /*      TEXTURE_MIN_FILTER */
        /*      TEXTURE_WRAP_S */
        /*      TEXTURE_WRAP_T */
        
        IMP_SCRIPT_CONST_UINT(COMPRESSED_TEXTURE_FORMATS     , GL_COMPRESSED_TEXTURE_FORMATS)
        
        /* HintMode */
        IMP_SCRIPT_CONST_UINT(DONT_CARE                      , GL_DONT_CARE)
        IMP_SCRIPT_CONST_UINT(FASTEST                        , GL_FASTEST)
        IMP_SCRIPT_CONST_UINT(NICEST                         , GL_NICEST)
        
        /* HintTarget */
        IMP_SCRIPT_CONST_UINT(GENERATE_MIPMAP_HINT            , GL_GENERATE_MIPMAP_HINT)
        
        /* DataType */
        IMP_SCRIPT_CONST_UINT(BYTE                           , GL_BYTE)
        IMP_SCRIPT_CONST_UINT(UNSIGNED_BYTE                  , GL_UNSIGNED_BYTE)
        IMP_SCRIPT_CONST_UINT(SHORT                          , GL_SHORT)
        IMP_SCRIPT_CONST_UINT(UNSIGNED_SHORT                 , GL_UNSIGNED_SHORT)
        IMP_SCRIPT_CONST_UINT(INT                            , GL_INT)
        IMP_SCRIPT_CONST_UINT(UNSIGNED_INT                   , GL_UNSIGNED_INT)
        IMP_SCRIPT_CONST_UINT(FLOAT                          , GL_FLOAT)
        
        /* PixelFormat */
        IMP_SCRIPT_CONST_UINT(DEPTH_COMPONENT                , GL_DEPTH_COMPONENT)
        IMP_SCRIPT_CONST_UINT(ALPHA                          , GL_ALPHA)
        IMP_SCRIPT_CONST_UINT(RGB                            , GL_RGB)
        IMP_SCRIPT_CONST_UINT(RGBA                           , GL_RGBA)
        IMP_SCRIPT_CONST_UINT(LUMINANCE                      , GL_LUMINANCE)
        IMP_SCRIPT_CONST_UINT(LUMINANCE_ALPHA                , GL_LUMINANCE_ALPHA)
        
        /* PixelType */
        /*      UNSIGNED_BYTE */
        IMP_SCRIPT_CONST_UINT(UNSIGNED_SHORT_4_4_4_4         , GL_UNSIGNED_SHORT_4_4_4_4)
        IMP_SCRIPT_CONST_UINT(UNSIGNED_SHORT_5_5_5_1         , GL_UNSIGNED_SHORT_5_5_5_1)
        IMP_SCRIPT_CONST_UINT(UNSIGNED_SHORT_5_6_5           , GL_UNSIGNED_SHORT_5_6_5)
        
        /* Shaders */
        IMP_SCRIPT_CONST_UINT(FRAGMENT_SHADER                  , GL_FRAGMENT_SHADER)
        IMP_SCRIPT_CONST_UINT(VERTEX_SHADER                    , GL_VERTEX_SHADER)
        IMP_SCRIPT_CONST_UINT(MAX_VERTEX_ATTRIBS               , GL_MAX_VERTEX_ATTRIBS)
        IMP_SCRIPT_CONST_UINT(MAX_VERTEX_UNIFORM_VECTORS       , GL_MAX_VERTEX_UNIFORM_VECTORS)
        IMP_SCRIPT_CONST_UINT(MAX_VARYING_VECTORS              , GL_MAX_VARYING_VECTORS)
        IMP_SCRIPT_CONST_UINT(MAX_COMBINED_TEXTURE_IMAGE_UNITS , GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)
        IMP_SCRIPT_CONST_UINT(MAX_VERTEX_TEXTURE_IMAGE_UNITS   , GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS)
        IMP_SCRIPT_CONST_UINT(MAX_TEXTURE_IMAGE_UNITS          , GL_MAX_TEXTURE_IMAGE_UNITS)
        IMP_SCRIPT_CONST_UINT(MAX_FRAGMENT_UNIFORM_VECTORS     , GL_MAX_FRAGMENT_UNIFORM_VECTORS)
        IMP_SCRIPT_CONST_UINT(SHADER_TYPE                      , GL_SHADER_TYPE)
        IMP_SCRIPT_CONST_UINT(DELETE_STATUS                    , GL_DELETE_STATUS)
        IMP_SCRIPT_CONST_UINT(LINK_STATUS                      , GL_LINK_STATUS)
        IMP_SCRIPT_CONST_UINT(VALIDATE_STATUS                  , GL_VALIDATE_STATUS)
        IMP_SCRIPT_CONST_UINT(ATTACHED_SHADERS                 , GL_ATTACHED_SHADERS)
        IMP_SCRIPT_CONST_UINT(ACTIVE_UNIFORMS                  , GL_ACTIVE_UNIFORMS)
        IMP_SCRIPT_CONST_UINT(ACTIVE_ATTRIBUTES                , GL_ACTIVE_ATTRIBUTES)
        IMP_SCRIPT_CONST_UINT(SHADING_LANGUAGE_VERSION         , GL_SHADING_LANGUAGE_VERSION)
        IMP_SCRIPT_CONST_UINT(CURRENT_PROGRAM                  , GL_CURRENT_PROGRAM)
        
        /* StencilFunction */
        IMP_SCRIPT_CONST_UINT(NEVER                          , GL_NEVER)
        IMP_SCRIPT_CONST_UINT(LESS                           , GL_LESS)
        IMP_SCRIPT_CONST_UINT(EQUAL                          , GL_EQUAL)
        IMP_SCRIPT_CONST_UINT(LEQUAL                         , GL_LEQUAL)
        IMP_SCRIPT_CONST_UINT(GREATER                        , GL_GREATER)
        IMP_SCRIPT_CONST_UINT(NOTEQUAL                       , GL_NOTEQUAL)
        IMP_SCRIPT_CONST_UINT(GEQUAL                         , GL_GEQUAL)
        IMP_SCRIPT_CONST_UINT(ALWAYS                         , GL_ALWAYS)
        
        /* StencilOp */
        /*      ZERO */
        IMP_SCRIPT_CONST_UINT(KEEP                           , GL_KEEP)
        IMP_SCRIPT_CONST_UINT(REPLACE                        , GL_REPLACE)
        IMP_SCRIPT_CONST_UINT(INCR                           , GL_INCR)
        IMP_SCRIPT_CONST_UINT(DECR                           , GL_DECR)
        IMP_SCRIPT_CONST_UINT(INVERT                         , GL_INVERT)
        IMP_SCRIPT_CONST_UINT(INCR_WRAP                      , GL_INCR_WRAP)
        IMP_SCRIPT_CONST_UINT(DECR_WRAP                      , GL_DECR_WRAP)
        
        /* StringName */
        IMP_SCRIPT_CONST_UINT(VENDOR                         , GL_VENDOR)
        IMP_SCRIPT_CONST_UINT(RENDERER                       , GL_RENDERER)
        IMP_SCRIPT_CONST_UINT(VERSION                        , GL_VERSION)
        
        /* TextureMagFilter */
        IMP_SCRIPT_CONST_UINT(NEAREST                        , GL_NEAREST)
        IMP_SCRIPT_CONST_UINT(LINEAR                         , GL_LINEAR)
        
        /* TextureMinFilter */
        /*      NEAREST */
        /*      LINEAR */
        IMP_SCRIPT_CONST_UINT(NEAREST_MIPMAP_NEAREST         , GL_NEAREST_MIPMAP_NEAREST)
        IMP_SCRIPT_CONST_UINT(LINEAR_MIPMAP_NEAREST          , GL_LINEAR_MIPMAP_NEAREST)
        IMP_SCRIPT_CONST_UINT(NEAREST_MIPMAP_LINEAR          , GL_NEAREST_MIPMAP_LINEAR)
        IMP_SCRIPT_CONST_UINT(LINEAR_MIPMAP_LINEAR           , GL_LINEAR_MIPMAP_LINEAR)
        
        /* TextureParameterName */
        IMP_SCRIPT_CONST_UINT(TEXTURE_MAG_FILTER             , GL_TEXTURE_MAG_FILTER)
        IMP_SCRIPT_CONST_UINT(TEXTURE_MIN_FILTER             , GL_TEXTURE_MIN_FILTER)
        IMP_SCRIPT_CONST_UINT(TEXTURE_WRAP_S                 , GL_TEXTURE_WRAP_S)
        IMP_SCRIPT_CONST_UINT(TEXTURE_WRAP_T                 , GL_TEXTURE_WRAP_T)
        
        /* TextureTarget */
        IMP_SCRIPT_CONST_UINT(TEXTURE_2D                     , GL_TEXTURE_2D)
        IMP_SCRIPT_CONST_UINT(TEXTURE                        , GL_TEXTURE)
        
        IMP_SCRIPT_CONST_UINT(TEXTURE_CUBE_MAP               , GL_TEXTURE_CUBE_MAP)
        IMP_SCRIPT_CONST_UINT(TEXTURE_BINDING_CUBE_MAP       , GL_TEXTURE_BINDING_CUBE_MAP)
        IMP_SCRIPT_CONST_UINT(TEXTURE_CUBE_MAP_POSITIVE_X    , GL_TEXTURE_CUBE_MAP_POSITIVE_X)
        IMP_SCRIPT_CONST_UINT(TEXTURE_CUBE_MAP_NEGATIVE_X    , GL_TEXTURE_CUBE_MAP_NEGATIVE_X)
        IMP_SCRIPT_CONST_UINT(TEXTURE_CUBE_MAP_POSITIVE_Y    , GL_TEXTURE_CUBE_MAP_POSITIVE_Y)
        IMP_SCRIPT_CONST_UINT(TEXTURE_CUBE_MAP_NEGATIVE_Y    , GL_TEXTURE_CUBE_MAP_NEGATIVE_Y)
        IMP_SCRIPT_CONST_UINT(TEXTURE_CUBE_MAP_POSITIVE_Z    , GL_TEXTURE_CUBE_MAP_POSITIVE_Z)
        IMP_SCRIPT_CONST_UINT(TEXTURE_CUBE_MAP_NEGATIVE_Z    , GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)
        IMP_SCRIPT_CONST_UINT(MAX_CUBE_MAP_TEXTURE_SIZE      , GL_MAX_CUBE_MAP_TEXTURE_SIZE)
        
        /* TextureUnit */
        IMP_SCRIPT_CONST_UINT(TEXTURE0                       , GL_TEXTURE0)
        IMP_SCRIPT_CONST_UINT(TEXTURE1                       , GL_TEXTURE1)
        IMP_SCRIPT_CONST_UINT(TEXTURE2                       , GL_TEXTURE2)
        IMP_SCRIPT_CONST_UINT(TEXTURE3                       , GL_TEXTURE3)
        IMP_SCRIPT_CONST_UINT(TEXTURE4                       , GL_TEXTURE4)
        IMP_SCRIPT_CONST_UINT(TEXTURE5                       , GL_TEXTURE5)
        IMP_SCRIPT_CONST_UINT(TEXTURE6                       , GL_TEXTURE6)
        IMP_SCRIPT_CONST_UINT(TEXTURE7                       , GL_TEXTURE7)
        IMP_SCRIPT_CONST_UINT(TEXTURE8                       , GL_TEXTURE8)
        IMP_SCRIPT_CONST_UINT(TEXTURE9                       , GL_TEXTURE9)
        IMP_SCRIPT_CONST_UINT(TEXTURE10                      , GL_TEXTURE10)
        IMP_SCRIPT_CONST_UINT(TEXTURE11                      , GL_TEXTURE11)
        IMP_SCRIPT_CONST_UINT(TEXTURE12                      , GL_TEXTURE12)
        IMP_SCRIPT_CONST_UINT(TEXTURE13                      , GL_TEXTURE13)
        IMP_SCRIPT_CONST_UINT(TEXTURE14                      , GL_TEXTURE14)
        IMP_SCRIPT_CONST_UINT(TEXTURE15                      , GL_TEXTURE15)
        IMP_SCRIPT_CONST_UINT(TEXTURE16                      , GL_TEXTURE16)
        IMP_SCRIPT_CONST_UINT(TEXTURE17                      , GL_TEXTURE17)
        IMP_SCRIPT_CONST_UINT(TEXTURE18                      , GL_TEXTURE18)
        IMP_SCRIPT_CONST_UINT(TEXTURE19                      , GL_TEXTURE19)
        IMP_SCRIPT_CONST_UINT(TEXTURE20                      , GL_TEXTURE20)
        IMP_SCRIPT_CONST_UINT(TEXTURE21                      , GL_TEXTURE21)
        IMP_SCRIPT_CONST_UINT(TEXTURE22                      , GL_TEXTURE22)
        IMP_SCRIPT_CONST_UINT(TEXTURE23                      , GL_TEXTURE23)
        IMP_SCRIPT_CONST_UINT(TEXTURE24                      , GL_TEXTURE24)
        IMP_SCRIPT_CONST_UINT(TEXTURE25                      , GL_TEXTURE25)
        IMP_SCRIPT_CONST_UINT(TEXTURE26                      , GL_TEXTURE26)
        IMP_SCRIPT_CONST_UINT(TEXTURE27                      , GL_TEXTURE27)
        IMP_SCRIPT_CONST_UINT(TEXTURE28                      , GL_TEXTURE28)
        IMP_SCRIPT_CONST_UINT(TEXTURE29                      , GL_TEXTURE29)
        IMP_SCRIPT_CONST_UINT(TEXTURE30                      , GL_TEXTURE30)
        IMP_SCRIPT_CONST_UINT(TEXTURE31                      , GL_TEXTURE31)
        IMP_SCRIPT_CONST_UINT(ACTIVE_TEXTURE                 , GL_ACTIVE_TEXTURE)
        
        /* TextureWrapMode */
        IMP_SCRIPT_CONST_UINT(REPEAT                         , GL_REPEAT)
        IMP_SCRIPT_CONST_UINT(CLAMP_TO_EDGE                  , GL_CLAMP_TO_EDGE)
        IMP_SCRIPT_CONST_UINT(MIRRORED_REPEAT                , GL_MIRRORED_REPEAT)
        
        /* Uniform Types */
        IMP_SCRIPT_CONST_UINT(FLOAT_VEC2                     , GL_FLOAT_VEC2)
        IMP_SCRIPT_CONST_UINT(FLOAT_VEC3                     , GL_FLOAT_VEC3)
        IMP_SCRIPT_CONST_UINT(FLOAT_VEC4                     , GL_FLOAT_VEC4)
        IMP_SCRIPT_CONST_UINT(INT_VEC2                       , GL_INT_VEC2)
        IMP_SCRIPT_CONST_UINT(INT_VEC3                       , GL_INT_VEC3)
        IMP_SCRIPT_CONST_UINT(INT_VEC4                       , GL_INT_VEC4)
        IMP_SCRIPT_CONST_UINT(BOOL                           , GL_BOOL)
        IMP_SCRIPT_CONST_UINT(BOOL_VEC2                      , GL_BOOL_VEC2)
        IMP_SCRIPT_CONST_UINT(BOOL_VEC3                      , GL_BOOL_VEC3)
        IMP_SCRIPT_CONST_UINT(BOOL_VEC4                      , GL_BOOL_VEC4)
        IMP_SCRIPT_CONST_UINT(FLOAT_MAT2                     , GL_FLOAT_MAT2)
        IMP_SCRIPT_CONST_UINT(FLOAT_MAT3                     , GL_FLOAT_MAT3)
        IMP_SCRIPT_CONST_UINT(FLOAT_MAT4                     , GL_FLOAT_MAT4)
        IMP_SCRIPT_CONST_UINT(SAMPLER_2D                     , GL_SAMPLER_2D)
        IMP_SCRIPT_CONST_UINT(SAMPLER_CUBE                   , GL_SAMPLER_CUBE)
        
        /* Vertex Arrays */
        IMP_SCRIPT_CONST_UINT(VERTEX_ATTRIB_ARRAY_ENABLED        , GL_VERTEX_ATTRIB_ARRAY_ENABLED)
        IMP_SCRIPT_CONST_UINT(VERTEX_ATTRIB_ARRAY_SIZE           , GL_VERTEX_ATTRIB_ARRAY_SIZE)
        IMP_SCRIPT_CONST_UINT(VERTEX_ATTRIB_ARRAY_STRIDE         , GL_VERTEX_ATTRIB_ARRAY_STRIDE)
        IMP_SCRIPT_CONST_UINT(VERTEX_ATTRIB_ARRAY_TYPE           , GL_VERTEX_ATTRIB_ARRAY_TYPE)
        IMP_SCRIPT_CONST_UINT(VERTEX_ATTRIB_ARRAY_NORMALIZED     , GL_VERTEX_ATTRIB_ARRAY_NORMALIZED)
        IMP_SCRIPT_CONST_UINT(VERTEX_ATTRIB_ARRAY_POINTER        , GL_VERTEX_ATTRIB_ARRAY_POINTER)
        IMP_SCRIPT_CONST_UINT(VERTEX_ATTRIB_ARRAY_BUFFER_BINDING , GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING)
        
        /* Read Format */
        IMP_SCRIPT_CONST_UINT(IMPLEMENTATION_COLOR_READ_TYPE   , GL_IMPLEMENTATION_COLOR_READ_TYPE)
        IMP_SCRIPT_CONST_UINT(IMPLEMENTATION_COLOR_READ_FORMAT , GL_IMPLEMENTATION_COLOR_READ_FORMAT)
        
        /* Shader Source */
        IMP_SCRIPT_CONST_UINT(COMPILE_STATUS                 , GL_COMPILE_STATUS)
        
        /* Shader Precision-Specified Types */
        IMP_SCRIPT_CONST_UINT(LOW_FLOAT                      , GL_LOW_FLOAT)
        IMP_SCRIPT_CONST_UINT(MEDIUM_FLOAT                   , GL_MEDIUM_FLOAT)
        IMP_SCRIPT_CONST_UINT(HIGH_FLOAT                     , GL_HIGH_FLOAT)
        IMP_SCRIPT_CONST_UINT(LOW_INT                        , GL_LOW_INT)
        IMP_SCRIPT_CONST_UINT(MEDIUM_INT                     , GL_MEDIUM_INT)
        IMP_SCRIPT_CONST_UINT(HIGH_INT                       , GL_HIGH_INT)
        
        /* Framebuffer Object. */
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER                    , GL_FRAMEBUFFER)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER                   , GL_RENDERBUFFER)
        
        IMP_SCRIPT_CONST_UINT(RGBA4                          , GL_RGBA4)
        IMP_SCRIPT_CONST_UINT(RGB5_A1                        , GL_RGB5_A1)
        IMP_SCRIPT_CONST_UINT(RGB565                         , GL_RGB565)
        IMP_SCRIPT_CONST_UINT(DEPTH_COMPONENT16              , GL_DEPTH_COMPONENT16)
//        IMP_SCRIPT_CONST_UINT(STENCIL_INDEX                  , GL_STENCIL_INDEX)
        IMP_SCRIPT_CONST_UINT(STENCIL_INDEX8                 , GL_STENCIL_INDEX8)
        IMP_SCRIPT_CONST_UINT(DEPTH_STENCIL                  , GL_DEPTH_STENCIL)
        
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_WIDTH             , GL_RENDERBUFFER_WIDTH)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_HEIGHT            , GL_RENDERBUFFER_HEIGHT)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_INTERNAL_FORMAT   , GL_RENDERBUFFER_INTERNAL_FORMAT)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_RED_SIZE          , GL_RENDERBUFFER_RED_SIZE)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_GREEN_SIZE        , GL_RENDERBUFFER_GREEN_SIZE)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_BLUE_SIZE         , GL_RENDERBUFFER_BLUE_SIZE)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_ALPHA_SIZE        , GL_RENDERBUFFER_ALPHA_SIZE)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_DEPTH_SIZE        , GL_RENDERBUFFER_DEPTH_SIZE)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_STENCIL_SIZE      , GL_RENDERBUFFER_STENCIL_SIZE)
        
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE           , GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE)
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_ATTACHMENT_OBJECT_NAME           , GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME)
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL         , GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL)
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE , GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE)
        
        IMP_SCRIPT_CONST_UINT(COLOR_ATTACHMENT0              , GL_COLOR_ATTACHMENT0)
        IMP_SCRIPT_CONST_UINT(DEPTH_ATTACHMENT               , GL_DEPTH_ATTACHMENT)
        IMP_SCRIPT_CONST_UINT(STENCIL_ATTACHMENT             , GL_STENCIL_ATTACHMENT)
        IMP_SCRIPT_CONST_UINT(DEPTH_STENCIL_ATTACHMENT       , GL_DEPTH_STENCIL_ATTACHMENT)
        
        IMP_SCRIPT_CONST_UINT(NONE                           , GL_NONE)
        
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_COMPLETE                      , GL_FRAMEBUFFER_COMPLETE)
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_INCOMPLETE_ATTACHMENT         , GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT , GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_INCOMPLETE_DIMENSIONS         , GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS)
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_UNSUPPORTED                   , GL_FRAMEBUFFER_UNSUPPORTED)
        
        IMP_SCRIPT_CONST_UINT(FRAMEBUFFER_BINDING            , GL_FRAMEBUFFER_BINDING)
        IMP_SCRIPT_CONST_UINT(RENDERBUFFER_BINDING           , GL_RENDERBUFFER_BINDING)
        IMP_SCRIPT_CONST_UINT(MAX_RENDERBUFFER_SIZE          , GL_MAX_RENDERBUFFER_SIZE)
        
        IMP_SCRIPT_CONST_UINT(INVALID_FRAMEBUFFER_OPERATION  , GL_INVALID_FRAMEBUFFER_OPERATION)
        
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
            
            IMP_SCRIPT_METHOD(Context,getSupportedExtensions)
            IMP_SCRIPT_METHOD(Context,getExtension)

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
            glActiveTexture(kk::script::toUintArgument(ctx, 0, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_attachShader(duk_context * ctx) {
            
            Program * p = dynamic_cast<Program *>(kk::script::toObjectArgument(ctx, 0));
            Shader * s = dynamic_cast<Shader *>(kk::script::toObjectArgument(ctx, 1));
            
            if(p && s) {
                glAttachShader(p->value(), s->value()); KK_GL_ERROR(ctx)
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_bindAttribLocation(duk_context * ctx) {
            
            Program * p = dynamic_cast<Program *>(kk::script::toObjectArgument(ctx, 0));
            
            if(p ) {
                glBindAttribLocation(p->value(),
                                     kk::script::toUintArgument(ctx, 1, 0),
                                     kk::script::toStringArgument(ctx, 2, "").c_str()); KK_GL_ERROR(ctx)
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_bindBuffer(duk_context * ctx) {
            
            Buffer * p = dynamic_cast<Buffer *>(kk::script::toObjectArgument(ctx, 1));
            
            glBindBuffer(kk::script::toUintArgument(ctx, 0, 0), p ? p->value() : 0); KK_GL_ERROR(ctx)
            
            return 0;
        }
        
        duk_ret_t Context::duk_bindFramebuffer(duk_context * ctx) {
            
            GLenum target = kk::script::toUintArgument(ctx, 0, 0);
            
            Framebuffer * p = dynamic_cast<Framebuffer *>(kk::script::toObjectArgument(ctx, 1));
            
            glBindFramebuffer(target, p ? p->value() : 0); KK_GL_ERROR(ctx)
            
            return 0;
        }
        
        duk_ret_t Context::duk_bindRenderbuffer(duk_context * ctx) {
            
            Renderbuffer * p = dynamic_cast<Renderbuffer *>(kk::script::toObjectArgument(ctx, 1));
            
            glBindRenderbuffer(kk::script::toUintArgument(ctx, 0, 0), p ? p->value() : 0); KK_GL_ERROR(ctx)
            
            return 0;
        }
        
        duk_ret_t Context::duk_bindTexture(duk_context * ctx) {
            
            Texture * p = dynamic_cast<Texture *>(kk::script::toObjectArgument(ctx, 1));
            
            glBindTexture(kk::script::toUintArgument(ctx, 0, 0), p ? p->value() : 0); KK_GL_ERROR(ctx)
            
            return 0;
        }
        
        duk_ret_t Context::duk_blendColor(duk_context * ctx) {
            glBlendColor(kk::script::toDoubleArgument(ctx, 0, 0),
                         kk::script::toDoubleArgument(ctx, 1, 0),
                         kk::script::toDoubleArgument(ctx, 2, 0),
                         kk::script::toDoubleArgument(ctx, 3, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_blendEquation(duk_context * ctx) {
            glBlendEquation(kk::script::toUintArgument(ctx, 0,0 )); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_blendEquationSeparate(duk_context * ctx) {
            glBlendEquationSeparate(kk::script::toUintArgument(ctx, 0,0 ),
                                    kk::script::toUintArgument(ctx, 1,0 )); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_blendFunc(duk_context * ctx) {
            glBlendFunc(kk::script::toUintArgument(ctx, 0,0 ),
                        kk::script::toUintArgument(ctx, 1,0 )); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_blendFuncSeparate(duk_context * ctx) {
            glBlendFuncSeparate(kk::script::toUintArgument(ctx, 0,0 ),
                                kk::script::toUintArgument(ctx, 1,0 ),
                                kk::script::toUintArgument(ctx, 2,0 ),
                                kk::script::toUintArgument(ctx, 3,0 )); KK_GL_ERROR(ctx)
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
                                 kk::script::toUintArgument(ctx, 2,0 )); KK_GL_ERROR(ctx)
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
                                    data); KK_GL_ERROR(ctx)
                }
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_checkFramebufferStatus(duk_context * ctx) {
            GLenum v = glCheckFramebufferStatus(kk::script::toUintArgument(ctx, 0,0 )); KK_GL_ERROR(ctx)
            duk_push_uint(ctx, v);
            return 1;
        }
        
        duk_ret_t Context::duk_clear(duk_context * ctx) {
            //glClear(kk::script::toUintArgument(ctx, 0,0 )); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_clearColor(duk_context * ctx) {
            glClearColor(kk::script::toDoubleArgument(ctx, 0,0 ),
                         kk::script::toDoubleArgument(ctx, 1,0 ),
                         kk::script::toDoubleArgument(ctx, 2,0 ),
                         kk::script::toDoubleArgument(ctx, 3,0 )); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_clearDepth(duk_context * ctx) {
            glClearDepthf(kk::script::toDoubleArgument(ctx, 0,0 )); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_clearStencil(duk_context * ctx) {
            glClearStencil(kk::script::toIntArgument(ctx, 0,0 )); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_colorMask(duk_context * ctx) {
            glColorMask(kk::script::toBooleanArgument(ctx, 0,false),
                        kk::script::toBooleanArgument(ctx, 1,false),
                        kk::script::toBooleanArgument(ctx, 2,false),
                        kk::script::toBooleanArgument(ctx, 3,false)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_compileShader(duk_context * ctx) {
            
            Shader * v = dynamic_cast<Shader *>(kk::script::toObjectArgument(ctx, 0));
            
            if(v) {
                glCompileShader(v->value()); KK_GL_ERROR(ctx)
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_compressedTexImage2D(duk_context * ctx) {
            
            GLenum target           = kk::script::toUintArgument(ctx, 0, 0);
            GLint level             = kk::script::toIntArgument (ctx, 1, 0);
            GLenum internalformat   = kk::script::toUintArgument(ctx, 2, 0);
            GLsizei width           = kk::script::toUintArgument(ctx, 3, 0);
            GLsizei height          = kk::script::toUintArgument(ctx, 4, 0);
            GLint border            = kk::script::toIntArgument (ctx, 5, 0);
            
            int top = duk_get_top(ctx);
            
            if(top > 6 && duk_is_buffer_data(ctx, -top + 6)) {
                
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 6, &n);
                
                glCompressedTexImage2D(target, level, internalformat, width, height, border, (GLsizei) n, data); KK_GL_ERROR(ctx)
                
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_compressedTexSubImage2D(duk_context * ctx) {
            
            GLenum target           = kk::script::toUintArgument(ctx, 0, 0);
            GLint level             = kk::script::toIntArgument (ctx, 1, 0);
            GLint xoffset           = kk::script::toIntArgument (ctx, 2, 0);
            GLint yoffset           = kk::script::toIntArgument (ctx, 3, 0);
            GLsizei width           = kk::script::toUintArgument(ctx, 4, 0);
            GLsizei height          = kk::script::toUintArgument(ctx, 5, 0);
            GLenum format           = kk::script::toUintArgument(ctx, 6, 0);
            
            int top = duk_get_top(ctx);
            
            if(top > 7 && duk_is_buffer_data(ctx, -top + 7)) {
                
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 7, &n);
                
                glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, (GLsizei) n, data); KK_GL_ERROR(ctx)
                
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_copyTexImage2D(duk_context * ctx) {
            
            GLenum target           = kk::script::toUintArgument(ctx, 0, 0);
            GLint level             = kk::script::toIntArgument (ctx, 1, 0);
            GLenum internalformat   = kk::script::toUintArgument(ctx, 2, 0);
            GLint x                 = kk::script::toIntArgument (ctx, 3, 0);
            GLint y                 = kk::script::toIntArgument (ctx, 4, 0);
            GLsizei width           = kk::script::toUintArgument(ctx, 5, 0);
            GLsizei height          = kk::script::toUintArgument(ctx, 6, 0);
            GLint border            = kk::script::toIntArgument (ctx, 7, 0);
            
            glCopyTexImage2D(target, level, internalformat, x, y, width, height, border); KK_GL_ERROR(ctx)
            
            return 0;
        }
        
        duk_ret_t Context::duk_copyTexSubImage2D(duk_context * ctx) {
            
            GLenum target           = kk::script::toUintArgument(ctx, 0, 0);
            GLint level             = kk::script::toIntArgument (ctx, 1, 0);
            GLint xoffset           = kk::script::toIntArgument (ctx, 2, 0);
            GLint yoffset           = kk::script::toIntArgument (ctx, 3, 0);
            GLint x                 = kk::script::toIntArgument (ctx, 4, 0);
            GLint y                 = kk::script::toIntArgument (ctx, 5, 0);
            GLsizei width           = kk::script::toUintArgument(ctx, 6, 0);
            GLsizei height          = kk::script::toUintArgument(ctx, 7, 0);
            
            glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height); KK_GL_ERROR(ctx)
            
            return 0;
        }
        
        duk_ret_t Context::duk_createBuffer(duk_context * ctx) {
            GLuint v = 0;
            glGenBuffers(1, &v); KK_GL_ERROR(ctx)
            kk::script::PushObject(ctx, new Buffer(v));
            return 1;
        }
        
        duk_ret_t Context::duk_createFramebuffer(duk_context * ctx) {
            GLuint v = 0;
            glGenFramebuffers(1, &v); KK_GL_ERROR(ctx)
            kk::script::PushObject(ctx, new Framebuffer(v));
            return 1;
        }
        duk_ret_t Context::duk_createProgram(duk_context * ctx) {
            GLuint v = glCreateProgram(); KK_GL_ERROR(ctx)
            kk::script::PushObject(ctx, new Program(v));
            return 1;
        }
        duk_ret_t Context::duk_createRenderbuffer(duk_context * ctx) {
            GLuint v = 0;
            glGenRenderbuffers(1, &v); KK_GL_ERROR(ctx)
            kk::script::PushObject(ctx, new Renderbuffer(v));
            return 1;
        }
        duk_ret_t Context::duk_createShader(duk_context * ctx) {
            GLuint v = glCreateShader(kk::script::toUintArgument(ctx, 0, GL_VERTEX_SHADER)); KK_GL_ERROR(ctx)
            kk::script::PushObject(ctx, new Shader(v));
            return 1;
        }
        
        duk_ret_t Context::duk_createTexture(duk_context * ctx) {
            GLuint v = 0;
            glGenTextures(1, &v); KK_GL_ERROR(ctx)
            kk::script::PushObject(ctx, new Texture(v));
            return 1;
        }
        
        duk_ret_t Context::duk_cullFace(duk_context * ctx) {
            glCullFace(kk::script::toUintArgument(ctx, 0, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_deleteBuffer(duk_context * ctx) {
            Buffer * v = dynamic_cast<Buffer *>(kk::script::toObjectArgument(ctx,0));
            if(v != nullptr) {
                GLuint i = v->value();
                glDeleteBuffers(1, &i); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        
        duk_ret_t Context::duk_deleteFramebuffer(duk_context * ctx) {
            
            Framebuffer * v = dynamic_cast<Framebuffer *>(kk::script::toObjectArgument(ctx,0));
            if(v != nullptr) {
                GLuint i = v->value();
                glDeleteFramebuffers(1, &i); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        
        duk_ret_t Context::duk_deleteProgram(duk_context * ctx) {
            Program * v = dynamic_cast<Program *>(kk::script::toObjectArgument(ctx,0));
            if(v != nullptr) {
                glDeleteProgram(v->value()); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        
        duk_ret_t Context::duk_deleteRenderbuffer(duk_context * ctx) {
            Renderbuffer * v = dynamic_cast<Renderbuffer *>(kk::script::toObjectArgument(ctx,0));
            if(v != nullptr) {
                GLuint i = v->value();
                glDeleteRenderbuffers(1, &i); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        
        duk_ret_t Context::duk_deleteShader(duk_context * ctx) {
            Shader * v = dynamic_cast<Shader *>(kk::script::toObjectArgument(ctx,0));
            if(v != nullptr) {
                glDeleteShader(v->value()); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        
        duk_ret_t Context::duk_deleteTexture(duk_context * ctx) {
            Texture * v = dynamic_cast<Texture *>(kk::script::toObjectArgument(ctx,0));
            if(v != nullptr) {
                GLuint i = v->value();
                glDeleteTextures(1, &i); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        
        duk_ret_t Context::duk_depthFunc(duk_context * ctx) {
            glDepthFunc(kk::script::toUintArgument(ctx, 0, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_depthMask(duk_context * ctx) {
            glDepthMask(kk::script::toBooleanArgument(ctx, 0, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_depthRange(duk_context * ctx) {
            glDepthRangef(kk::script::toDoubleArgument(ctx, 0, 0),
                          kk::script::toDoubleArgument(ctx, 0, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_detachShader(duk_context * ctx) {
            Program * p = dynamic_cast<Program *>(kk::script::toObjectArgument(ctx, 0));
            Shader * s = dynamic_cast<Shader *>(kk::script::toObjectArgument(ctx, 1));
            if(p && s) {
                glDetachShader(p->value(), s->value()); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        
        duk_ret_t Context::duk_disable(duk_context * ctx) {
            glDisable(kk::script::toUintArgument(ctx, 0, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_disableVertexAttribArray(duk_context * ctx) {
            glDisableVertexAttribArray(kk::script::toUintArgument(ctx, 0, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_drawArrays(duk_context * ctx) {
            glDrawArrays(kk::script::toUintArgument(ctx, 0, 0),
                         kk::script::toIntArgument(ctx, 1, 0),
                         kk::script::toUintArgument(ctx, 2, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_drawElements(duk_context * ctx) {
            glDrawElements(kk::script::toUintArgument(ctx, 0, 0),
                           kk::script::toUintArgument(ctx, 1, 0),
                           kk::script::toUintArgument(ctx, 2, 0),
                           (void *)(long)kk::script::toUintArgument(ctx, 3, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_enable(duk_context * ctx) {
            glEnable(kk::script::toUintArgument(ctx, 0, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_enableVertexAttribArray(duk_context * ctx) {
            glEnableVertexAttribArray(kk::script::toUintArgument(ctx, 0, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_finish(duk_context * ctx) {
            glFinish(); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_flush(duk_context * ctx) {
            glFlush(); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_framebufferRenderbuffer(duk_context * ctx) {
            
            GLenum target               = kk::script::toUintArgument(ctx, 0, 0);
            GLenum attachment           = kk::script::toUintArgument(ctx, 1, 0);
            GLenum renderbuffertarget   = kk::script::toUintArgument(ctx, 2, 0);
            
            Renderbuffer * v = dynamic_cast<Renderbuffer *>( kk::script::toObjectArgument(ctx, 3) );
            
            if(attachment == GL_DEPTH_STENCIL_ATTACHMENT) {
                glFramebufferRenderbuffer(target,
                                          GL_DEPTH_ATTACHMENT,
                                          renderbuffertarget,
                                          v ? v->value() : 0); KK_GL_ERROR(ctx)
                glFramebufferRenderbuffer(target,
                                          GL_STENCIL_ATTACHMENT,
                                          renderbuffertarget,
                                          v ? v->value() : 0); KK_GL_ERROR(ctx)
            }
            if(v) {
                glFramebufferRenderbuffer(target,
                                          attachment,
                                          renderbuffertarget,
                                          v ? v->value() : 0); KK_GL_ERROR(ctx)
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
                                       kk::script::toIntArgument(ctx, 4, 0)); KK_GL_ERROR(ctx)
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_frontFace(duk_context * ctx) {
            glFrontFace(kk::script::toUintArgument(ctx, 0, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_generateMipmap(duk_context * ctx) {
            glGenerateMipmap(kk::script::toUintArgument(ctx, 0, 0)); KK_GL_ERROR(ctx)
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
                                  name); KK_GL_ERROR(ctx)
                
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
                                  name); KK_GL_ERROR(ctx)
                
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
                
                glGetAttachedShaders(v->value(), 64, &n, vs); KK_GL_ERROR(ctx)
                
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
                GLint i = glGetAttribLocation(v->value(), kk::script::toStringArgument(ctx, 1, "").c_str()); KK_GL_ERROR(ctx)
                duk_push_int(ctx, i);
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getBufferParameter(duk_context * ctx) {
            GLint v = 0;
            glGetBufferParameteriv(kk::script::toUintArgument(ctx, 0, 0),
                                   kk::script::toUintArgument(ctx, 1, 0),
                                   &v); KK_GL_ERROR(ctx)
            duk_push_int(ctx, v);
            return 1;
        }
        
        duk_ret_t Context::duk_getParameter(duk_context * ctx) {
            
            GLenum name = kk::script::toUintArgument(ctx, 0, 0);
        
            {
                kk::CString v = (kk::CString) glGetString(name);
                
                if(v != nullptr && glGetError() == 0) {
                    duk_push_string(ctx, v);
                    return 1;
                }
            }
            
            {
                GLint v = 0;
                glGetIntegerv(name, &v);
                if(glGetError() == 0) {
                    duk_push_int(ctx, v);
                    return 1;
                }
            }
            
            {
                GLfloat v = 0;
                glGetFloatv(name, &v);
                if(glGetError() == 0) {
                    duk_push_number(ctx, v);
                    return 1;
                }
            }
            
            {
                GLboolean v = 0;
                glGetBooleanv(name, &v);
                if(glGetError() == 0) {
                    duk_push_boolean(ctx, v);
                    return 1;
                }
            }
            
            KK_GL_ERROR(ctx)
            
            return 0;
        }
        
        duk_ret_t Context::duk_getError(duk_context * ctx) {
            GLenum v = glGetError(); KK_GL_ERROR(ctx)
            duk_push_uint(ctx, v);
            return 1;
        }
        
        duk_ret_t Context::duk_getFramebufferAttachmentParameter(duk_context * ctx) {
            
            GLint v = 0;
            glGetFramebufferAttachmentParameteriv(kk::script::toUintArgument(ctx, 0, 0),
                                                  kk::script::toUintArgument(ctx, 1, 0),
                                                  kk::script::toUintArgument(ctx, 2, 0),
                                                  &v); KK_GL_ERROR(ctx)
            
            duk_push_int(ctx, v);
            
            return 1;
        }
        
        duk_ret_t Context::duk_getProgramParameter(duk_context * ctx) {
            
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                GLint i = 0;
                glGetProgramiv(v->value(), kk::script::toUintArgument(ctx, 1, 0), &i); KK_GL_ERROR(ctx)
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
                glGetProgramInfoLog(v->value(), sizeof(data), &n, data); KK_GL_ERROR(ctx)
                duk_push_lstring(ctx, data, n);
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getRenderbufferParameter(duk_context * ctx) {
            GLint v = 0;
            glGetRenderbufferParameteriv(kk::script::toUintArgument(ctx, 0, 0),
                                         kk::script::toUintArgument(ctx, 1, 0),
                                         &v); KK_GL_ERROR(ctx)
            
            duk_push_int(ctx, v);
            
            return 1;
        }
        
        duk_ret_t Context::duk_getShaderParameter(duk_context * ctx) {
            
            Shader * v = dynamic_cast<Shader *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                GLint i = 0;
                glGetShaderiv(v->value(), kk::script::toUintArgument(ctx, 1, 0), &i); KK_GL_ERROR(ctx)
                duk_push_int(ctx, i);
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getShaderPrecisionFormat(duk_context * ctx) {
            GLenum shadertype = kk::script::toUintArgument(ctx, 0, 0);
            GLenum precisiontype = kk::script::toUintArgument(ctx, 1, 0);
            GLint range = 0;
            GLint precision = 0;
            glGetShaderPrecisionFormat(shadertype,
                                       precisiontype,
                                       &range,
                                       &precision); KK_GL_ERROR(ctx)
            duk_push_object(ctx);
            duk_push_int(ctx, range);
            duk_put_prop_string(ctx, -2, "rangeMin");
            
            duk_push_int(ctx, range);
            duk_put_prop_string(ctx, -2, "rangeMax");
            
            duk_push_int(ctx, precision);
            duk_put_prop_string(ctx, -2, "precision");

            return 1;
        }
        
        duk_ret_t Context::duk_getShaderInfoLog(duk_context * ctx) {
            
            Shader * v = dynamic_cast<Shader *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                char data[2048];
                GLsizei n = 0;
                glGetShaderInfoLog(v->value(), sizeof(data), &n, data); KK_GL_ERROR(ctx)
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
                glGetShaderSource(v->value(), sizeof(data), &n, data); KK_GL_ERROR(ctx)
                duk_push_lstring(ctx, data, n);
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getTexParameter(duk_context * ctx) {
            
            GLint i = 0;
            
            glGetTexParameteriv(kk::script::toUintArgument(ctx, 0, 0),
                                kk::script::toUintArgument(ctx, 1, 0), &i); KK_GL_ERROR(ctx)
            
            duk_push_int(ctx, i);
    
            return 1;
        }
        
        duk_ret_t Context::duk_getUniform(duk_context * ctx) {
            
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                GLint i = 0;
                glGetUniformiv(v->value(),
                               kk::script::toIntArgument(ctx, 1, 0),
                               &i); KK_GL_ERROR(ctx)
                duk_push_int(ctx, i);
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getUniformLocation(duk_context * ctx) {
            
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                
                int i = glGetUniformLocation(v->value(), kk::script::toStringArgument(ctx, 1, "").c_str()); KK_GL_ERROR(ctx)
                
                duk_push_int(ctx, i);
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getVertexAttrib(duk_context * ctx) {
            
            GLint i = 0;
            
            glGetVertexAttribiv(kk::script::toUintArgument(ctx, 0, 0),
                                kk::script::toUintArgument(ctx, 1, 0), &i); KK_GL_ERROR(ctx)
            
            duk_push_int(ctx, i);
            return 1;
        }
        
        duk_ret_t Context::duk_getVertexAttribOffset(duk_context * ctx) {
            
            return 0;
        }
        
        
        duk_ret_t Context::duk_hint(duk_context * ctx) {
            glHint(kk::script::toUintArgument(ctx, 0, 0),
                   kk::script::toUintArgument(ctx, 1, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_isBuffer(duk_context * ctx) {
            Buffer * v = dynamic_cast<Buffer *>( kk::script::toObjectArgument(ctx, 0) );
            duk_push_boolean(ctx, v != nullptr && glIsBuffer(v->value())); KK_GL_ERROR(ctx)
            return 1;
        }
        
        duk_ret_t Context::duk_isEnabled(duk_context * ctx) {
            glIsEnabled(kk::script::toUintArgument(ctx, 0, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_isFramebuffer(duk_context * ctx) {
            Framebuffer * v = dynamic_cast<Framebuffer *>( kk::script::toObjectArgument(ctx, 0) );
            duk_push_boolean(ctx, v != nullptr && glIsFramebuffer(v->value())); KK_GL_ERROR(ctx)
            return 1;
        }
        
        duk_ret_t Context::duk_isProgram(duk_context * ctx) {
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            duk_push_boolean(ctx, v != nullptr && glIsProgram(v->value())); KK_GL_ERROR(ctx)
            return 1;
        }
        
        duk_ret_t Context::duk_isRenderbuffer(duk_context * ctx) {
            Renderbuffer * v = dynamic_cast<Renderbuffer *>( kk::script::toObjectArgument(ctx, 0) );
            duk_push_boolean(ctx, v != nullptr && glIsRenderbuffer(v->value())); KK_GL_ERROR(ctx)
            return 1;
        }
        
        duk_ret_t Context::duk_isShader(duk_context * ctx) {
            Shader * v = dynamic_cast<Shader *>( kk::script::toObjectArgument(ctx, 0) );
            duk_push_boolean(ctx, v != nullptr && glIsShader(v->value())); KK_GL_ERROR(ctx)
            return 1;
        }
        
        duk_ret_t Context::duk_isTexture(duk_context * ctx) {
            Texture * v = dynamic_cast<Texture *>( kk::script::toObjectArgument(ctx, 0) );
            duk_push_boolean(ctx, v != nullptr && glIsTexture(v->value())); KK_GL_ERROR(ctx)
            return 1;
        }
        
        duk_ret_t Context::duk_lineWidth(duk_context * ctx) {
            glLineWidth(kk::script::toDoubleArgument(ctx, 0, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_linkProgram(duk_context * ctx) {
            Program * v = dynamic_cast<Program *>( kk::script::toObjectArgument(ctx, 0) );
            if(v != nullptr) {
                glLinkProgram(v->value()); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        
        duk_ret_t Context::duk_pixelStorei(duk_context * ctx) {
            glPixelStorei(kk::script::toUintArgument(ctx, 0, 0),
                          kk::script::toIntArgument(ctx, 1, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_polygonOffset(duk_context * ctx) {
            glPolygonOffset(kk::script::toDoubleArgument(ctx, 0, 0),
                            kk::script::toDoubleArgument(ctx, 1, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_readPixels(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 6 && duk_is_buffer_data(ctx, -top + 6)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 6, &n);
                glReadPixels(kk::script::toIntArgument(ctx, 0, 0),
                             kk::script::toIntArgument(ctx, 1, 0),
                             kk::script::toUintArgument(ctx, 2, 0),
                             kk::script::toUintArgument(ctx, 3, 0),
                             kk::script::toUintArgument(ctx, 4, 0),
                             kk::script::toUintArgument(ctx, 5, 0),
                             data); KK_GL_ERROR(ctx)
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_renderbufferStorage(duk_context * ctx) {
            
            GLenum target           = kk::script::toUintArgument(ctx, 0, 0);
            GLenum internalformat   = kk::script::toUintArgument(ctx, 1, 0);
            GLsizei width           = kk::script::toUintArgument(ctx, 2, 0);
            GLsizei height          = kk::script::toUintArgument(ctx, 3, 0);
            
            if(internalformat == GL_DEPTH_STENCIL) {
                glRenderbufferStorageOES(target, GL_DEPTH24_STENCIL8_OES, width, height); KK_GL_ERROR(ctx)
            } else {
                glRenderbufferStorage(target, internalformat, width, height); KK_GL_ERROR(ctx)
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_sampleCoverage(duk_context * ctx) {
            
            glSampleCoverage(kk::script::toDoubleArgument(ctx, 0, 0),
                             kk::script::toBooleanArgument(ctx, 1, 0)); KK_GL_ERROR(ctx)
            
            return 0;
        }
        
        duk_ret_t Context::duk_scissor(duk_context * ctx) {
            
            glScissor(kk::script::toUintArgument(ctx, 0, 0),
                      kk::script::toUintArgument(ctx, 1, 0),
                      kk::script::toUintArgument(ctx, 2, 0),
                      kk::script::toUintArgument(ctx, 3, 0)); KK_GL_ERROR(ctx)
            
            return 0;
        }
        
        duk_ret_t Context::duk_shaderSource(duk_context * ctx) {
            
            Shader * v = dynamic_cast<Shader *>( kk::script::toObjectArgument(ctx, 0) );
            
            if(v) {
                
                kk::String s = kk::script::toStringArgument(ctx, 1, "");
                kk::CString code = s.c_str();
                
                glShaderSource(v->value(), 1, &code, NULL); KK_GL_ERROR(ctx)
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_stencilFunc(duk_context * ctx) {
            
            glStencilFunc(kk::script::toUintArgument(ctx, 0, 0),
                          kk::script::toIntArgument(ctx, 1, 0),
                          kk::script::toUintArgument(ctx, 2, 0)); KK_GL_ERROR(ctx)
            
            return 0;
        }
        
        duk_ret_t Context::duk_stencilFuncSeparate(duk_context * ctx) {
            
            glStencilFuncSeparate(kk::script::toUintArgument(ctx, 0, 0),
                                  kk::script::toUintArgument(ctx, 1, 0),
                                  kk::script::toIntArgument(ctx, 2, 0),
                                  kk::script::toUintArgument(ctx, 3, 0)); KK_GL_ERROR(ctx)
            
            return 0;
        }
        
        duk_ret_t Context::duk_stencilMask(duk_context * ctx) {
            glStencilMask(kk::script::toUintArgument(ctx, 0, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_stencilMaskSeparate(duk_context * ctx) {
            glStencilMaskSeparate(kk::script::toUintArgument(ctx, 0, 0),
                                  kk::script::toUintArgument(ctx, 1, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_stencilOp(duk_context * ctx) {
            
            glStencilOp(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toUintArgument(ctx, 1, 0),
                        kk::script::toUintArgument(ctx, 2, 0)); KK_GL_ERROR(ctx)
            
            return 0;
        }
        
        duk_ret_t Context::duk_stencilOpSeparate(duk_context * ctx) {
            
            glStencilOpSeparate(kk::script::toUintArgument(ctx, 0, 0),
                                kk::script::toUintArgument(ctx, 1, 0),
                                kk::script::toUintArgument(ctx, 2, 0),
                                kk::script::toUintArgument(ctx, 3, 0)); KK_GL_ERROR(ctx)
            
            return 0;
        }
        
        duk_ret_t Context::duk_texImage2D(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 8) {
                
                GLenum target           = kk::script::toUintArgument(ctx, 0, 0);
                GLint level             = kk::script::toIntArgument (ctx, 1, 0);
                GLenum internalformat   = kk::script::toUintArgument(ctx, 2, 0);
                GLsizei width           = kk::script::toUintArgument(ctx, 3, 0);
                GLsizei height          = kk::script::toUintArgument(ctx, 4, 0);
                GLint border            = kk::script::toIntArgument (ctx, 5, 0);
                GLenum format           = kk::script::toUintArgument(ctx, 6, 0);
                GLenum type             = kk::script::toUintArgument(ctx, 7, 0);
                
                
                if(duk_is_buffer_data(ctx, -top + 8)) {
                    size_t n = 0;
                    void * data = duk_get_buffer_data(ctx, -top + 8, &n);
                    glTexImage2D(target, level, internalformat, width, height, border, format, type, data); KK_GL_ERROR(ctx)
                }
                
            } else {
                
                GLenum target           = kk::script::toUintArgument(ctx, 0, 0);
                GLint level             = kk::script::toIntArgument (ctx, 1, 0);
                GLenum internalformat   = kk::script::toUintArgument(ctx, 2, 0);
                GLenum format           = kk::script::toUintArgument(ctx, 3, 0);
                GLenum type             = kk::script::toUintArgument(ctx, 4, 0);
                
                kk::CG::Image * image = dynamic_cast<kk::CG::Image *>(kk::script::toObjectArgument(ctx, 5));
                
                if(image && image->isCopyPixels()) {
                    GLsizei width = image->width();
                    GLsizei height = image->height();
                    GLint border = 0 ;
                    void * data = malloc(width * height * 4);
                    memset(data, 0, width * height * 4);
                    image->copyPixels(data);
                    glTexImage2D(target, level, internalformat, width, height, border, format, type, data); KK_GL_ERROR(ctx)
                    free(data);
                }
                
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_texParameterf(duk_context * ctx) {
            glTexParameterf(kk::script::toUintArgument(ctx, 0, 0),
                            kk::script::toUintArgument(ctx, 1, 0),
                            kk::script::toDoubleArgument(ctx, 2, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_texParameteri(duk_context * ctx) {
            glTexParameteri(kk::script::toUintArgument(ctx, 0, 0),
                            kk::script::toUintArgument(ctx, 1, 0),
                            kk::script::toIntArgument(ctx, 2, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_texSubImage2D(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 8) {
                
                GLenum target           = kk::script::toUintArgument(ctx, 0, 0);
                GLint level             = kk::script::toIntArgument (ctx, 1, 0);
                GLint xoffset           = kk::script::toIntArgument (ctx, 2, 0);
                GLint yoffset           = kk::script::toIntArgument (ctx, 3, 0);
                GLsizei width           = kk::script::toUintArgument(ctx, 4, 0);
                GLsizei height          = kk::script::toUintArgument(ctx, 5, 0);
                GLenum format           = kk::script::toUintArgument(ctx, 6, 0);
                GLenum type             = kk::script::toUintArgument(ctx, 7, 0);
                
                if(duk_is_buffer_data(ctx, -top + 7)) {
                    size_t n = 0;
                    void * data = duk_get_buffer_data(ctx, -top + 7, &n);
                    glTexSubImage2D(target, level,xoffset,yoffset, width, height, format, type, data); KK_GL_ERROR(ctx)
                }
                
            } else {
                
                GLenum target           = kk::script::toUintArgument(ctx, 0, 0);
                GLint level             = kk::script::toIntArgument (ctx, 1, 0);
                GLint xoffset           = kk::script::toIntArgument (ctx, 2, 0);
                GLint yoffset           = kk::script::toIntArgument (ctx, 3, 0);
                GLenum format           = kk::script::toUintArgument(ctx, 4, 0);
                GLenum type             = kk::script::toUintArgument(ctx, 5, 0);
                
                kk::CG::Image * image = dynamic_cast<kk::CG::Image *>(kk::script::toObjectArgument(ctx, 6));
                
                if(image && image->isCopyPixels()) {
                    GLsizei width = image->width();
                    GLsizei height = image->height();
                    void * data = malloc(width * height * 4);
                    memset(data, 0, width * height * 4);
                    image->copyPixels(data);
                    glTexSubImage2D(target, level, xoffset,yoffset, width, height, format, type, data); KK_GL_ERROR(ctx)
                    free(data);
                }
                
            }
        
            return 0;
        }
        
        duk_ret_t Context::duk_uniform1f(duk_context * ctx) {
            glUniform1f(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toDoubleArgument(ctx, 1, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        duk_ret_t Context::duk_uniform1fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform1fv(kk::script::toUintArgument(ctx, 0, 0),
                             (GLsizei) (n / sizeof(GLfloat)),
                             (GLfloat *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        
        duk_ret_t Context::duk_uniform1i(duk_context * ctx) {
            glUniform1i(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toIntArgument(ctx, 1, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_uniform1iv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform1iv(kk::script::toUintArgument(ctx, 0, 0),
                             (GLsizei) (n / sizeof(GLint)),
                             (GLint *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        duk_ret_t Context::duk_uniform2f(duk_context * ctx) {
            glUniform2f(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toDoubleArgument(ctx, 1, 0),
                        kk::script::toDoubleArgument(ctx, 2, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        duk_ret_t Context::duk_uniform2fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform2fv(kk::script::toUintArgument(ctx, 0, 0),
                             (GLsizei) (n / sizeof(GLfloat) / 2),
                             (GLfloat *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        duk_ret_t Context::duk_uniform2i(duk_context * ctx) {
            glUniform2i(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toIntArgument(ctx, 1, 0),
                        kk::script::toIntArgument(ctx, 2, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        duk_ret_t Context::duk_uniform2iv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform2iv(kk::script::toUintArgument(ctx, 0, 0),
                             (GLsizei) (n / sizeof(GLint) / 2),
                             (GLint *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        duk_ret_t Context::duk_uniform3f(duk_context * ctx) {
            glUniform3f(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toDoubleArgument(ctx, 1, 0),
                        kk::script::toDoubleArgument(ctx, 2, 0),
                        kk::script::toDoubleArgument(ctx, 3, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        duk_ret_t Context::duk_uniform3fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform3fv(kk::script::toUintArgument(ctx, 0, 0),
                             (GLsizei) (n / sizeof(GLfloat) / 3),
                             (GLfloat *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        duk_ret_t Context::duk_uniform3i(duk_context * ctx) {
            glUniform3i(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toIntArgument(ctx, 1, 0),
                        kk::script::toIntArgument(ctx, 2, 0),
                        kk::script::toIntArgument(ctx, 3, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        duk_ret_t Context::duk_uniform3iv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform3iv(kk::script::toUintArgument(ctx, 0, 0),
                             (GLsizei) (n / sizeof(GLint) / 3),
                             (GLint *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        duk_ret_t Context::duk_uniform4f(duk_context * ctx) {
            glUniform4f(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toDoubleArgument(ctx, 1, 0),
                        kk::script::toDoubleArgument(ctx, 2, 0),
                        kk::script::toDoubleArgument(ctx, 3, 0),
                        kk::script::toDoubleArgument(ctx, 4, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        duk_ret_t Context::duk_uniform4fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform4fv(kk::script::toUintArgument(ctx, 0, 0),
                             (GLsizei) (n / sizeof(GLfloat) / 4),
                             (GLfloat *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        duk_ret_t Context::duk_uniform4i(duk_context * ctx) {
            glUniform4i(kk::script::toUintArgument(ctx, 0, 0),
                        kk::script::toIntArgument(ctx, 1, 0),
                        kk::script::toIntArgument(ctx, 2, 0),
                        kk::script::toIntArgument(ctx, 3, 0),
                        kk::script::toIntArgument(ctx, 4, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        duk_ret_t Context::duk_uniform4iv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glUniform4iv(kk::script::toUintArgument(ctx, 0, 0),
                                   (GLsizei) (n / sizeof(GLint) / 4),
                                   (GLint *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        
        duk_ret_t Context::duk_uniformMatrix2fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 2 && duk_is_buffer_data(ctx, -top + 2)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 2, &n);
                glUniformMatrix2fv(kk::script::toUintArgument(ctx, 0, 0),
                                   (GLsizei) (n / sizeof(GLfloat) / 4),
                                   kk::script::toBooleanArgument(ctx, 1, 0),
                                   (GLfloat *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        duk_ret_t Context::duk_uniformMatrix3fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 2 && duk_is_buffer_data(ctx, -top + 2)) {
                GLint location = kk::script::toIntArgument(ctx, 0, 0);
                GLboolean transpose = kk::script::toBooleanArgument(ctx, 1, 0);
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 2, &n);
                glUniformMatrix3fv(location,
                                   (GLsizei) (n / sizeof(GLfloat) / 9),
                                   transpose,
                                   (GLfloat *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        duk_ret_t Context::duk_uniformMatrix4fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 2 && duk_is_buffer_data(ctx, -top + 2)) {
                GLint location = kk::script::toIntArgument(ctx, 0, 0);
                GLboolean transpose = kk::script::toBooleanArgument(ctx, 1, 0);
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 2, &n);
                glUniformMatrix4fv(location,
                                   (GLsizei) (n / sizeof(GLfloat) / 16),
                                   transpose,
                                   (GLfloat *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        
        duk_ret_t Context::duk_useProgram(duk_context * ctx) {
            
            Program * p = dynamic_cast<Program *>(kk::script::toObjectArgument(ctx, 0));
            
            glUseProgram(p ? p->value() : 0); KK_GL_ERROR(ctx)
            
            return 0;
        }
        
        duk_ret_t Context::duk_validateProgram(duk_context * ctx) {
            
            Program * p = dynamic_cast<Program *>(kk::script::toObjectArgument(ctx, 0));
            
            if(p) {
                glValidateProgram(p->value()); KK_GL_ERROR(ctx)
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_vertexAttrib1f(duk_context * ctx) {
            glVertexAttrib1f(kk::script::toUintArgument(ctx, 0, 0),
                             kk::script::toDoubleArgument(ctx, 1, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_vertexAttrib1fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glVertexAttrib1fv(kk::script::toUintArgument(ctx, 0, 0), (GLfloat *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        duk_ret_t Context::duk_vertexAttrib2f(duk_context * ctx) {
            glVertexAttrib2f(kk::script::toUintArgument(ctx, 0, 0),
                             kk::script::toDoubleArgument(ctx, 1, 0),
                             kk::script::toDoubleArgument(ctx, 2, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        duk_ret_t Context::duk_vertexAttrib2fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glVertexAttrib2fv(kk::script::toUintArgument(ctx, 0, 0), (GLfloat *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        duk_ret_t Context::duk_vertexAttrib3f(duk_context * ctx) {
            glVertexAttrib3f(kk::script::toUintArgument(ctx, 0, 0),
                             kk::script::toDoubleArgument(ctx, 1, 0),
                             kk::script::toDoubleArgument(ctx, 2, 0),
                             kk::script::toDoubleArgument(ctx, 3, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        duk_ret_t Context::duk_vertexAttrib3fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glVertexAttrib3fv(kk::script::toUintArgument(ctx, 0, 0), (GLfloat *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        duk_ret_t Context::duk_vertexAttrib4f(duk_context * ctx) {
            glVertexAttrib4f(kk::script::toUintArgument(ctx, 0, 0),
                             kk::script::toDoubleArgument(ctx, 1, 0),
                             kk::script::toDoubleArgument(ctx, 2, 0),
                             kk::script::toDoubleArgument(ctx, 3, 0),
                             kk::script::toDoubleArgument(ctx, 4, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        duk_ret_t Context::duk_vertexAttrib4fv(duk_context * ctx) {
            int top = duk_get_top(ctx);
            if(top > 1 && duk_is_buffer_data(ctx, -top + 1)) {
                size_t n = 0;
                void * data = duk_get_buffer_data(ctx, -top + 1, &n);
                glVertexAttrib4fv(kk::script::toUintArgument(ctx, 0, 0), (GLfloat *) data); KK_GL_ERROR(ctx)
            }
            return 0;
        }
        duk_ret_t Context::duk_vertexAttribPointer(duk_context * ctx) {
            glVertexAttribPointer(kk::script::toUintArgument(ctx, 0, 0),
                                  kk::script::toIntArgument (ctx, 1, 0),
                                  kk::script::toUintArgument(ctx, 2, 0),
                                  kk::script::toBooleanArgument(ctx, 3, 0),
                                  kk::script::toUintArgument(ctx, 4, 0),
                                  (void *) (long) kk::script::toIntArgument(ctx, 5, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_viewport(duk_context * ctx) {
            glViewport(kk::script::toIntArgument(ctx, 0, 0),
                       kk::script::toIntArgument(ctx, 1, 0),
                       kk::script::toUintArgument(ctx, 2, 0),
                       kk::script::toUintArgument(ctx, 3, 0)); KK_GL_ERROR(ctx)
            return 0;
        }
        
        duk_ret_t Context::duk_getSupportedExtensions(duk_context * ctx) {
            
            std::vector<kk::String> vs;
            
            kk::CStringSplit((kk::CString) glGetString(GL_EXTENSIONS), " ", vs); KK_GL_ERROR(ctx)
            
            duk_push_array(ctx);
            
            duk_uarridx_t i =0;
            
            std::vector<kk::String>::iterator p = vs.begin();
            
            while(p != vs.end()) {
                
                kk::String& v = * p;
                
                if(!v.empty()) {
                    duk_push_string(ctx, v.c_str());
                    duk_put_prop_index(ctx, -2, i);
                }
                
                p ++;
            }
            
            return 1;
        }
        
        duk_ret_t Context::duk_getExtension(duk_context * ctx) {
            
            std::set<kk::String> vs;
            
            kk::CStringSplit((kk::CString) glGetString(GL_EXTENSIONS), " ", vs); KK_GL_ERROR(ctx)
            
            std::set<kk::String>::iterator i = vs.find(kk::script::toStringArgument(ctx, 0, "").c_str());
            
            if(i != vs.end()) {
                duk_push_object(ctx);
                return 1;
            }
            
            return 0;
        }
        

    }
    
}
