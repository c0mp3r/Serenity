/*
 * Copyright (c) 2022, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

namespace Web::HTML {

// https://html.spec.whatwg.org/multipage/origin.html#sandboxing-flag-set
struct SandboxingFlagSet {
    enum Flag {
        SandboxedNavigation = 1u << 0u,
        SandboxedAuxiliaryNavigation = 1u << 1u,
        SandboxedTopLevelNavigationWithoutUserActivation = 1u << 2u,
        SandboxedTopLevelNavigationWithUserActivation = 1u << 3u,
        SandboxedPlugins = 1u << 4u,
        SandboxedOrigin = 1u << 5u,
        SandboxedForms = 1u << 6u,
        SandboxedPointerLock = 1u << 7u,
        SandboxedScripts = 1u << 8u,
        SandboxedAutomaticFeatures = 1u << 9u,
        SandboxedDocumentDomain = 1u << 10u,
        SandboxPropagatesToAuxiliaryBrowsingContexts = 1u << 11u,
        SandboxedModals = 1u << 12u,
        SandboxedOrientationLock = 1u << 13u,
        SandboxedPresentation = 1u << 14u,
        SandboxedDownloads = 1u << 15u,
        SandboxedCustomProtocols = 1u << 16u,
    };

    bool is_empty() const { return flags == 0; }

    u32 flags { 0 };
};

}
