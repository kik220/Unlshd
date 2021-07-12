#include "../nfc_i.h"

enum SubmenuIndex {
    SubmenuIndexRead,
    SubmenuIndexRunScript,
    SubmenuIndexSaved,
    SubmenuIndexAddManualy,
    SubmenuIndexDebug,
};

void nfc_scene_start_submenu_callback(void* context, uint32_t index) {
    Nfc* nfc = (Nfc*)context;

    view_dispatcher_send_custom_event(nfc->nfc_common.view_dispatcher, index);
}

const void nfc_scene_start_on_enter(void* context) {
    Nfc* nfc = (Nfc*)context;
    Submenu* submenu = nfc->submenu;

    submenu_add_item(
        submenu, "Read card", SubmenuIndexRead, nfc_scene_start_submenu_callback, nfc);
    submenu_add_item(
        submenu,
        "Run special action",
        SubmenuIndexRunScript,
        nfc_scene_start_submenu_callback,
        nfc);
    submenu_add_item(
        submenu, "Saved cards", SubmenuIndexSaved, nfc_scene_start_submenu_callback, nfc);
    submenu_add_item(
        submenu, "Add manually", SubmenuIndexAddManualy, nfc_scene_start_submenu_callback, nfc);
    submenu_add_item(submenu, "Debug", SubmenuIndexDebug, nfc_scene_start_submenu_callback, nfc);
    submenu_set_selected_item(
        submenu, scene_manager_get_scene_state(nfc->scene_manager, NfcSceneStart));

    view_dispatcher_switch_to_view(nfc->nfc_common.view_dispatcher, NfcViewMenu);
}

const bool nfc_scene_start_on_event(void* context, SceneManagerEvent event) {
    Nfc* nfc = (Nfc*)context;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == SubmenuIndexRead) {
            scene_manager_set_scene_state(nfc->scene_manager, NfcSceneStart, SubmenuIndexRead);
            scene_manager_next_scene(nfc->scene_manager, NfcSceneReadCard);
            return true;
        } else if(event.event == SubmenuIndexRunScript) {
            scene_manager_set_scene_state(
                nfc->scene_manager, NfcSceneStart, SubmenuIndexRunScript);
            scene_manager_next_scene(nfc->scene_manager, NfcSceneScriptsMenu);
            return true;
        } else if(event.event == SubmenuIndexSaved) {
            scene_manager_set_scene_state(nfc->scene_manager, NfcSceneStart, SubmenuIndexSaved);
            scene_manager_next_scene(nfc->scene_manager, NfcSceneFileSelect);
            return true;
        } else if(event.event == SubmenuIndexAddManualy) {
            scene_manager_set_scene_state(
                nfc->scene_manager, NfcSceneStart, SubmenuIndexAddManualy);
            scene_manager_next_scene(nfc->scene_manager, NfcSceneSetType);
            return true;
        } else if(event.event == SubmenuIndexDebug) {
            scene_manager_set_scene_state(nfc->scene_manager, NfcSceneStart, SubmenuIndexDebug);
            scene_manager_next_scene(nfc->scene_manager, NfcSceneDebugMenu);
            return true;
        }
    }
    return false;
}

const void nfc_scene_start_on_exit(void* context) {
    Nfc* nfc = (Nfc*)context;

    submenu_clean(nfc->submenu);
}
