//Copyright (C) 2011 Jack Culhane - jackculhane@gmail.com
//
//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

#define PURPLE_PLUGINS

#include <plugin.h>
#include <notify.h>
#include <version.h>
#include <pluginpref.h>

#define PLUGIN_ID "core-buzz_auto_reply"
#define REPLY_MSG "/plugins/" PLUGIN_ID "/reply_msg"

static PurplePlugin *buzz_plugin;


//Callback function to send autoreply when buzz is received
static void buzz_cb(PurpleAccount *account, char *who, PurpleConversation *conv, guint type) {

    PurpleConvIm *im = purple_conversation_get_im_data(conv);
    const char *msg = purple_prefs_get_string(REPLY_MSG);

    purple_conv_im_send(im, msg);
}


static gboolean plugin_load(PurplePlugin *plugin) {
    
    void *conv = purple_conversations_get_handle(); 
    buzz_plugin = plugin;
    
    //Connect attention signal to our callback function
    purple_signal_connect( conv, "got-attention", buzz_plugin, PURPLE_CALLBACK(buzz_cb), NULL ); 

    return TRUE;
}


//Set up preference frame so we can set the message
static PurplePluginPrefFrame *get_prefs_frame(PurplePlugin *plugin) {

    PurplePluginPrefFrame *frame;
    PurplePluginPref *pref;

    frame = purple_plugin_pref_frame_new();
    
	pref = purple_plugin_pref_new_with_name_and_label(REPLY_MSG, "Autoreply Message:");
	purple_plugin_pref_frame_add(frame, pref);

    return frame;
}


//Pidgin will call get_prefs_frame to get the preferences frame
static PurplePluginUiInfo ui_info = {
   get_prefs_frame,
   0,
   NULL,
   NULL,
   NULL,
   NULL
};


static PurplePluginInfo info = {
    PURPLE_PLUGIN_MAGIC,                                 //Purple Magic
    PURPLE_MAJOR_VERSION,                                //Major Version
    PURPLE_MINOR_VERSION,                                //Minor Version
    PURPLE_PLUGIN_STANDARD,                              //Type
    NULL,                                                //UI Requirement
    0,                                                   //FLAGS
    NULL,                                                //Dependencies
    PURPLE_PRIORITY_DEFAULT,                             //Priority

    PLUGIN_ID,                                           //ID
    "Buzz AutoReply",                                    //Name
    "1.0",                                               //Version
    "Automatically reply to received buzzes",            //Summary
    "Automatically reply to received buzzes",            //Description
    "Jack Culhane <jackculhane@gmail.com>",              //Author
    "https://github.com/jcul/Pidgin-Buzz-Autoreply",     //Website

    plugin_load,                                         //Load Function
    NULL,                                                //Unload
    NULL,                                                //Destroy

    NULL,                                                //UI Struct
    NULL,
    &ui_info,                                            //Prefs
    NULL,                                                //Actions

    NULL,                                                //Reserved
    NULL,
    NULL,
    NULL,
};


//Set up the reply message setting and set default to "Ouch!"
static void
init_plugin(PurplePlugin *plugin)
{
	purple_prefs_add_none("/plugins/" PLUGIN_ID);
    purple_prefs_add_string(REPLY_MSG, "Ouch!");
}


PURPLE_INIT_PLUGIN(clever_chat, init_plugin, info)
