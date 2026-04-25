#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>
#include <zmk/behavior.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#define DPI_BUTTON_POSITION 3

static int helix_dpi_listener(const zmk_event_t *eh) {
    const struct zmk_position_state_changed *ev = as_zmk_position_state_changed(eh);
    if (!ev || !ev->state || ev->position != DPI_BUTTON_POSITION) {
        return ZMK_EV_EVENT_BUBBLE;
    }
    struct zmk_behavior_binding binding = {
        .behavior_dev = "dpi_cycle",
        .param1 = 1,
        .param2 = 0,
    };
    struct zmk_behavior_binding_event event = {
        .layer = 0,
        .position = ev->position,
        .timestamp = ev->timestamp,
    };
    behavior_keymap_binding_pressed(&binding, event);
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(helix_dpi_hook, helix_dpi_listener);
ZMK_SUBSCRIPTION(helix_dpi_hook, zmk_position_state_changed);
