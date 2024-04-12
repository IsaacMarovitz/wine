/*
 * Copyright 2024 Isaac Marovitz
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "wined3d_private.h"
#include "wined3d_mtl.h"

WINE_DEFAULT_DEBUG_CHANNEL(d3d);

static MTLCompareFunction mtl_compare_func_from_wined3d(enum wined3d_cmp_func op)
{
    switch (op)
    {
        case WINED3D_CMP_NEVER:
            return MTLCompareFunctionNever;
        case WINED3D_CMP_ALWAYS:
            return MTLCompareFunctionNever;
        case WINED3D_CMP_LESS:
            return MTLCompareFunctionLess;
        case WINED3D_CMP_LESSEQUAL:
            return MTLCompareFunctionLessEqual;
        case WINED3D_CMP_GREATER:
            return MTLCompareFunctionGreater;
        case WINED3D_CMP_GREATEREQUAL:
            return MTLCompareFunctionGreaterEqual;
        case WINED3D_CMP_EQUAL:
            return MTLCompareFunctionEqual;
        case WINED3D_CMP_NOTEQUAL:
            return MTLCompareFunctionNotEqual;
    }
}

static MTLBlendFactor mtl_blend_factor_from_wined3d(enum wined3d_blend blend,
        const struct wined3d_format *dst_format, bool alpha)
{
    switch (blend)
    {
        case WINED3D_BLEND_ZERO:
            return MTLBlendFactorZero;
        case WINED3D_BLEND_ONE:
            return MTLBlendFactorOne;
        case WINED3D_BLEND_SRCCOLOR:
            return MTLBlendFactorSourceColor;
        case WINED3D_BLEND_INVSRCCOLOR:
            return MTLBlendFactorOneMinusSourceColor;
        case WINED3D_BLEND_SRCALPHA:
            return MTLBlendFactorSourceAlpha;
        case WINED3D_BLEND_INVSRCALPHA:
            return MTLBlendFactorOneMinusSourceAlpha;
        case WINED3D_BLEND_DESTALPHA:
            if (dst_format->alpha_size)
                return MTLBlendFactorDestinationAlpha;
            return MTLBlendFactorOne;
        case WINED3D_BLEND_INVDESTALPHA:
            if (dst_format->alpha_size)
                return MTLBlendFactorOneMinusDestinationAlpha;
            return MTLBlendFactorZero;
        case WINED3D_BLEND_DESTCOLOR:
            return MTLBlendFactorDestinationColor;
        case WINED3D_BLEND_INVDESTCOLOR:
            return MTLBlendFactorOneMinusDestinationColor;
        case WINED3D_BLEND_SRCALPHASAT:
            return MTLBlendFactorSourceAlphaSaturated;
        case WINED3D_BLEND_BLENDFACTOR:
            if (alpha)
                return MTLBlendFactorBlendAlpha;
            return MTLBlendFactorBlendColor;
        case WINED3D_BLEND_INVBLENDFACTOR:
            if (alpha)
                return MTLBlendFactorOneMinusBlendAlpha;
            return MTLBlendFactorOneMinusBlendColor;
        case WINED3D_BLEND_SRC1COLOR:
            return MTLBlendFactorSource1Color;
        case WINED3D_BLEND_INVSRC1COLOR:
            return MTLBlendFactorOneMinusSource1Color;
        case WINED3D_BLEND_SRC1ALPHA:
            return MTLBlendFactorSource1Alpha;
        case WINED3D_BLEND_INVSRC1ALPHA:
            return MTLBlendFactorOneMinusSourceAlpha;
        default:
            FIXME("Unhandled blend %#x.\n", blend);
            return MTLBlendFactorZero;
    }
}

static MTLBlendOperation mtl_blend_op_from_wined3d(enum wined3d_blend_op op)
{
    switch (op)
    {
        case WINED3D_BLEND_OP_ADD:
            return MTLBlendOperationAdd;
        case WINED3D_BLEND_OP_SUBTRACT:
            return MTLBlendOperationSubtract;
        case WINED3D_BLEND_OP_REVSUBTRACT:
            return MTLBlendOperationReverseSubtract;
        case WINED3D_BLEND_OP_MAX:
            return MTLBlendOperationMax;
        case WINED3D_BLEND_OP_MIN:
            return MTLBlendOperationMin
    }
}

static MTLColorWriteMask mtl_color_write_mask_from_wined3d(uint32_t wined3d_mask)
{
    MTLColorWriteMask mtl_mask = 0;

    if (wined3d_mask & WINED3DCOLORWRITEENABLE_RED)
        mtl_mask |= MTLColorWriteMaskRed;
    if (wined3d_mask & WINED3DCOLORWRITEENABLE_GREEN)
        mtl_mask |= MTLColorWriteMaskGreen;
    if (wined3d_mask & WINED3DCOLORWRITEENABLE_BLUE)
        mtl_mask |= MTLColorWriteMaskBlue;
    if (wined3d_mask & WINED3DCOLORWRITEENABLE_ALPHA)
        mtl_mask |= MTLColorWriteMaskAlpha;

    return mtl_mask;
}

static MTLCullMode mtl_cull_mode_from_wined3d(enum wined3d_cull mode)
{
    switch (mode)
    {
        case WINED3D_CULL_NONE:
            return MTLCullModeNone;
        case WINED3D_CULL_FRONT:
            return MTLCullModeFront;
        case WINED3D_CULL_BACK:
            return MTLCullModeBack;
    }
}

static MTLStencilOperation mtl_stencil_op_from_wined3d(enum wined3d_stencil_op op)
{
    switch (op)
    {
        case WINED3D_STENCIL_OP_KEEP:
            return MTLStencilOperationKeep;
        case WINED3D_STENCIL_OP_ZERO:
            return MTLStencilOperationZero;
        case WINED3D_STENCIL_OP_REPLACE:
            return MTLStencilOperationReplace;
        case WINED3D_STENCIL_OP_INCR_SAT:
            return MTLStencilOperationIncrementClamp;
        case WINED3D_STENCIL_OP_DECR_SAT:
            return MTLStencilOperationDecrementClamp;
        case WINED3D_STENCIL_OP_INVERT:
            return MTLStencilOperationInvert;
        case WINED3D_STENCIL_OP_INCR:
            return MTLStencilOperationIncrementWrap;
        case WINED3D_STENCIL_OP_DECR:
            return MTLStencilOperationDecrementWrap;
    }
}