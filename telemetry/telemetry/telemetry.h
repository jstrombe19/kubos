/*
 * Copyright (C) 2017 Kubos Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "ipc/pubsub.h"
#include "telemetry/config.h"
#include "telemetry/types.h"
#include <csp/arch/csp_thread.h>
#include <stdbool.h>

/**
 * Task used to receive incoming data from telemetry publishers.
 */
CSP_DEFINE_TASK(telemetry_rx_task);

/**
 * Performs basic telemetry connection and thread initialization. 
 * To be used in the main() prior to starting the scheduler.
 */
void telemetry_init();

/**
 * Performs cleanup on telemetry resources & threads.
 */
void telemetry_cleanup();

/**
 * Connects to the telemetry system - thread safe version.
 * @param conn pointer to pubsub_conn which will be used to receive future telemetry data.
 * @return bool true if successful, otherwise false
 */
bool telemetry_connect(pubsub_conn * conn);

/**
 * Internal connect function - not thread safe.
 * @param conn pointer to pubsub_conn which will be used to receive future telemetry data
 * @return bool true if successful, otherwise false
 */
bool kprv_telemetry_connect(pubsub_conn * conn);

/**
 * Subscribes the pubsub_conn to the specified topic.
 * @param conn pointer to pubsub_conn
 * @param topic_id topic to subscribe to
 * @return bool true if successful, otherwise false
 */
bool telemetry_subscribe(pubsub_conn * conn, uint16_t topic_id);

/**
 * Disconnects from the telemetry system.
 * @param conn pointer to pubsub_conn which is to be disconnected
 * @return bool true if successful, otherwise false
 */
bool telemetry_disconnect(pubsub_conn * conn);

/**
 * Unsubscribes a connection from a specific topic.
 * @param conn pointer to pubsub_conn which is to be unsubscribed
 * @param topic_id topic to remove subscription from
 * @return bool true if successful, otherwise false
 */
bool telemetry_unsubscribe(pubsub_conn * conn, uint16_t topic_id);

/**
 * Reads a telemetry packet from the telemetry server.
 * @param conn pubsub_connection to use for the request
 * @param packet pointer to telemetry_packet to store data in.
 * @return bool true if successful, otherwise false 
 */
bool telemetry_read(pubsub_conn conn, telemetry_packet * packet);

/**
 * Public facing telemetry input interface. Takes a telemetry_packet packet
 * and passes it through the telemetry system.
 * @param packet telemetry_packet to publish
 * @return bool true if successful, otherwise false
 */
bool telemetry_publish(telemetry_packet packet);

/**
 * @return int number of active telemetry subscribers
 */
int telemetry_num_subscribers();

#endif
