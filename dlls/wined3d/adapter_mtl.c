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

static HRESULT adapter_mtl_create_texture(struct wined3d_device *device,
        const struct wined3d_resource_desc *desc, unsigned int layout_count, unsigned int level_count,
        uint32_t flags, void *parent, const struct wined3d_parent_ops *parent_ops, struct wined3d_texture **texture)
{
    FIXME("Texture creation requested.");
}

static void adapter_mtl_destroy_texture(struct wined3d_texture *texture)
{
    FIXME("Texture destruction requested.");
}

static HRESULT adapter_mtl_create_rendertarget_view(const struct wined3d_view_desc *desc,
        struct wined3d_resource *resource, void *parent, const struct wined3d_parent_ops *parent_ops,
        struct wined3d_rendertarget_view **view)
{
    FIXME("Render target view creation requested.");
}

static void adapter_mtl_destroy_rendertarget_view(struct wined3d_rendertarget_view *view)
{
    FIXME("Render target view destruction requested.");
}

static HRESULT adapter_mtl_create_shader_resource_view(const struct wined3d_view_desc *desc,
        struct wined3d_resource *resource, void *parent, const struct wined3d_parent_ops *parent_ops,
        struct wined3d_shader_resource_view **view)
{
    FIXME("Shader resource view construction requested.");
}

static void adapter_mtl_destroy_shader_resource_view(struct wined3d_shader_resource_view *view)
{
    FIXME("Shader resource view destruction requested.");
}

static HRESULT adapter_mtl_create_unordered_access_view(const struct wined3d_view_desc *desc,
        struct wined3d_resource *resource, void* parent, const struct wined3d_parent_ops *parent_ops,
        struct wined3d_unordered_access_view **view)
{
    FIXME("Unordered access view construction requested.");
}

static void adapter_mtl_destroy_unordered_access_view(struct wined3d_unordered_access_view *view)
{
    FIXME("Unordered access view destruction requested.");
}

static HRESULT adapter_mtl_create_sampler(struct wined3d_device *device, const struct wined3d_sampler_desc *desc,
        void *parent, const struct wined3d_parent_ops *parent_ops, struct wined3d_sampler **sampler)
{
    FIXME("Sampler construction requested.");
}

static void adapter_mtl_destroy_sampler(struct wined3d_sampler *sampler)
{
    FIXME("Sampler destruction requested.");
}

static HRESULT adapter_mtl_create_query(struct wined3d_device *device, enum wined3d_query_type type,
        void *parent, const struct wined3d_parent_ops *parent_ops, struct wined3d_query **query)
{
    FIXME("Query creation requested.");
}

static void adapter_mtl_destroy_query(struct wined3d_query *query)
{
    FIXME("Query destruction requested.");
}

static void adapter_mtl_flush_context(struct wined3d_context *context)
{
    FIXME("Context flush requested.");
}

static void adapter_mtl_draw_primitive(struct wined3d_device *device,
        const struct wined3d_state *state, const struct wined3d_draw_parameters *parameters)
{
    FIXME("Primitive draw requested.");
}

static void adapter_mtl_dispatch_compute(struct wined3d_device *device,
        const struct wined3d_state *state, const struct wined3d_dispatch_parameters *parameters)
{
    FIXME("Compute dispatch requested.");
}

static void adapter_mtl_clear_uav(struct wined3d_context *context,
        struct wined3d_unordered_access_view *view, const struct wined3d_uvec4 *clear_value, bool fp)
{
    FIXME("UAV Clear requested.");
}

static void adapter_mtl_generate_mipmap(struct wined3d_context *context, struct wined3d_shader_resource_view *view)
{
    FIXME("Mipmap generation requested");
}

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
    .adapter_create_texture = adapter_mtl_create_texture,
    .adapter_destroy_texture = adapter_mtl_destroy_texture,
    .adapter_create_rendertarget_view = adapter_mtl_create_rendertarget_view,
    .adapter_destroy_rendertarget_view = adapter_mtl_destroy_rendertarget_view,
    .adapter_create_shader_resource_view = adapter_mtl_create_shader_resource_view,
    .adapter_destroy_shader_resource_view = adapter_mtl_destroy_shader_resource_view,
    .adapter_create_unordered_access_view = adapter_mtl_create_unordered_access_view,
    .adapter_destroy_unordered_access_view = adapter_mtl_destroy_unordered_access_view,
    .adapter_create_sampler = adapter_mtl_create_sampler,
    .adapter_destroy_sampler = adapter_mtl_destroy_sampler,
    .adapter_create_query = adapter_mtl_create_query,
    .adapter_destroy_query = adapter_mtl_destroy_query,
    .adapter_flush_context = adapter_mtl_flush_context,
    .adapter_draw_primitive = adapter_mtl_draw_primitive,
    .adapter_dispatch_compute = adapter_mtl_dispatch_compute,
    .adapter_clear_uav = adapter_mtl_clear_uav,
    .adapter_generate_mipmap = adapter_mtl_generate_mipmap,
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