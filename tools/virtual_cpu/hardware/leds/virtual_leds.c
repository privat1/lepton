/*
The contents of this file are subject to the Mozilla Public License Version 1.1
(the "License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for the
specific language governing rights and limitations under the License.

The Original Code is Lepton.

The Initial Developer of the Original Code is Philippe Le Boulanger.
Portions created by Philippe Le Boulanger are Copyright (C) 2011 <lepton.phlb@gmail.com>.
All Rights Reserved.

Contributor(s): Jean-Jacques Pitrolle <lepton.jjp@gmail.com>.

Alternatively, the contents of this file may be used under the terms of the eCos GPL license
(the  [eCos GPL] License), in which case the provisions of [eCos GPL] License are applicable
instead of those above. If you wish to allow use of your version of this file only under the
terms of the [eCos GPL] License and not to allow others to use your version of this file under
the MPL, indicate your decision by deleting  the provisions above and replace
them with the notice and other provisions required by the [eCos GPL] License.
If you do not delete the provisions above, a recipient may use your version of this file under
either the MPL or the [eCos GPL] License."
*/

#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

#include <sys/shm.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "virtual_leds.h"
#include "virtual_hardware.h"
#include "virtual_cpu.h"
#include "virtual_cpu_gui.h"

char leds_name[] = "/dev/leds0\0";

int virtual_leds_load(void * data);
int virtual_leds_open(void * data);
int virtual_leds_close(void * data);
int virtual_leds_read(void * data);
int virtual_leds_write(void * data);
int virtual_leds_seek(void * data);
int virtual_leds_ioctl(void * data);

hdwr_info_t virtual_leds = {
   leds_name,
   __fdev_not_fd,
   virtual_leds_load,
   virtual_leds_open,
   virtual_leds_close,
   virtual_leds_read,
   virtual_leds_write,
   virtual_leds_seek,
   virtual_leds_ioctl
};

//
static virtual_leds_t * leds_0_data = NULL;
static virtual_cpu_t * vcpu = NULL;
static short leds_ok=0;
static unsigned short leds_count;
static GtkWidget ** leds_ui_list;

//
int virtual_leds_load(void * data) {
   vcpu = (virtual_cpu_t *)data;
   //put data pointer in write place
   leds_0_data = (virtual_leds_t *)(vcpu->shm_base_addr + LEDS_OFFSET);
   DEBUG_TRACE("(F) %s load ok ..\n", virtual_leds.name);
   return 0;
}

//nothing to do
int virtual_leds_open(void * data) {
   virtual_cmd_t cmd={LEDS, OPS_OPEN};
   //
   leds_ok=1;
   while(write(1, (void *)&cmd, sizeof(virtual_cmd_t)) !=sizeof(virtual_cmd_t)) ;
   DEBUG_TRACE("(F) %s open ok..\n", virtual_leds.name);
   //
   return 0;
}

//
int virtual_leds_close(void * data) {
   virtual_cmd_t cmd={LEDS, OPS_CLOSE};
   //
   leds_ok=0;
   while(write(1, (void *)&cmd, sizeof(virtual_cmd_t)) !=sizeof(virtual_cmd_t)) ;
   DEBUG_TRACE("(F) %s open ok..\n", virtual_leds.name);
   //
   return 0;
}

//
int virtual_leds_read(void * data) {
   return 0;
}

//
int virtual_leds_write(void * data) {
   virtual_cmd_t cmd={LEDS, ACK};
   int i = 0;
   gboolean state=FALSE;
   if(leds_ok) {
      for(; i<leds_count; i++) {
         DEBUG_TRACE("%d ", leds_0_data->data_out[i]);
         state = (leds_0_data->data_out[i]) ? FALSE : TRUE;
         gtk_toggle_button_set_inconsistent((GtkToggleButton *)leds_ui_list[i], state); //gtk_toggle_button_set_mode((GtkToggleButton *)leds_ui_list[i], state);//gtk_toggle_button_set_active ((GtkToggleButton *)leds_ui_list[i], state);
      }
      DEBUG_TRACE("\r\n");
      while(write(1, (void *)&cmd, sizeof(virtual_cmd_t)) !=sizeof(virtual_cmd_t)) ;
   }
   return 0;
}

//nothing to do
int virtual_leds_seek(void * data) {
   return 0;
}

//nothing to do
int virtual_leds_ioctl(void * data) {
   return 0;
}

//
int virtual_leds_create_radio_button(GtkBuilder *builder, GtkWidget ** radio_button_list,
                                     int size) {
   int i = 0;
   char radio_button_name[RADIO_BUTTON_NAME_SIZE]={0};

   leds_ui_list = radio_button_list;

   for(; i<size; i++) {
      snprintf(radio_button_name, RADIO_BUTTON_NAME_SIZE,"%s%d",LEDS_PREFIX_NAME,i+1);
      //get button
      if(!(radio_button_list[i] = GTK_WIDGET(gtk_builder_get_object(builder,radio_button_name)))) {
         leds_count = i;
         DEBUG_TRACE("(F) virtual_leds : leds count %d\n", leds_count);
         return -1;
      }

      DEBUG_TRACE("(F) %s\n",radio_button_name);

   }
   return 0;
}
