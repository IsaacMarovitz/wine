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