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

#include <stdio.h>

#include "wined3d_private.h"
#include "wined3d_mtl.h"

WINE_DEFAULT_DEBUG_CHANNEL(d3d);

static const struct wined3d_adapter_ops wined3d_adapter_mtl_ops =
{
    .adapter_destroy = NULL,
    .adapter_create_device = NULL,
    .adapter_destroy_device = NULL,
    .adapter_acquire_context = NULL,
    .adapter_release_context = NULL,
    .adapter_get_wined3d_caps = NULL,
    .adapter_check_format = NULL,
    .adapter_init_3d = NULL,
    .adapter_uninit_3d = NULL,
    .adapter_map_bo_address = NULL,
    .adapter_unmap_bo_address = NULL,
    .adapter_copy_bo_address = NULL,
    .adapter_flush_bo_address = NULL,
    .adapter_alloc_bo = NULL,
    .adapter_destroy_bo = NULL,
    .adapter_create_swapchain = NULL,
    .adapter_destroy_swapchain = NULL,
    .adapter_create_buffer = NULL,
    .adapter_destroy_buffer = NULL,
    .adapter_create_texture = NULL,
    .adapter_destroy_texture = NULL,
    .adapter_create_rendertarget_view = NULL,
    .adapter_destroy_rendertarget_view = NULL,
    .adapter_create_shader_resource_view = NULL,
    .adapter_destroy_shader_resource_view = NULL,
    .adapter_create_unordered_access_view = NULL,
    .adapter_destroy_unordered_access_view = NULL,
    .adapter_create_sampler = NULL,
    .adapter_destroy_sampler = NULL,
    .adapter_create_query = NULL,
    .adapter_destroy_query = NULL,
    .adapter_flush_context = NULL,
    .adapter_draw_primitive = NULL,
    .adapter_dispatch_compute = NULL,
    .adapter_clear_uav = NULL,
    .adapter_generate_mipmap = NULL,
};

static BOOL wined3d_load_metal()
{
    return TRUE;
}

static BOOL wined3d_init_metal()
{
    if (!wined3d_load_metal())
        return FALSE;

    return TRUE;
}

static BOOL wined3d_adapter_mtl_init(struct wined3d_adapter_mtl *adapter_mtl,
        unsigned int ordinal, unsigned int wined3d_creation_flags)
{
    TRACE("adapter_vk %p, ordinal %u, wined3d_creation_flags %#x.\n",
          adapter_vk, ordinal, wined3d_creation_flags);

    if (!wined3d_init_metal())
    {
        WARN("Failed to initialize Metal.\n");
        return FALSE;
    }

    return TRUE;
}

struct wined3d_adapter *wined3d_adapter_mtl_create(unsigned int ordinal,
        unsigned int wined3d_creation_flags)
{
    struct wined3d_adapter_mtl *adapter_mtl;

    if (!(adapter_mtl = calloc(1, sizeof(*adapter_mtl))))
        return NULL;

    if (!wined3d_adapter_mtl_init(adapter_mtl, ordinal, wined3d_creation_flags))
    {
        free(adapter_mtl);
        return NULL;
    }

    TRACE("Created adapter %p.\n", adapter_mtl);

    return &adapter_mtl->a;
}