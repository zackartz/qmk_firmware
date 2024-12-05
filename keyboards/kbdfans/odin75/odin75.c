/* Copyright 2022 DZTECH <moyi4681@live.cn>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "raw_hid.h"
#include "print.h"
#include "oled_driver.h"

#include "string.h"

// What the screen look like if no connection is established. This shows a "No connection" message
char current_screen[62 * 128] = {0};

/*
 * Payload structure. Index identifies where on the OLED to write to.
 * Report IDs aren't used but cause a pain (not writing, occasionally being stripped off etc.)
 * For this reason, the first byte should always be "1"
 * |  1  | 2 | 3 --------- 32 |
 * |REPID|IDX|     DATA       |
 */
static const int PAYLOAD_SIZE = 32;

void raw_hid_receive(uint8_t *data, uint8_t length) {
    printf("raw_hid_receive bytes:%d first:%0X\r\n", length, *data);
    // TODO: Read report ID to determine the OLED screen to write to
    /* raw_hid_send(data, length); */
    uint8_t *index = &data[1];

    memcpy(&current_screen[(PAYLOAD_SIZE - 2) * (*index)], &data[2], (PAYLOAD_SIZE - 2));
    printf("copied\n");
}

static void render_oled(void) {
    oled_write_raw(current_screen, sizeof(current_screen));
}

bool oled_task_kb(void) {
    render_oled();
    return false;
}
