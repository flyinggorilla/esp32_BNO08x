/**
 * @file BNO08xRptAcceleration.cpp
 * @author Myles Parfeniuk
 */

#include "BNO08xRptAcceleration.hpp"

/**
 * @brief Updates accelerometer data from decoded sensor event.
 *
 * @param sensor_val The sh2_SensorValue_t struct used in sh2_decodeSensorEvent() call.
 *
 * @return void, nothing to return
 */
void BNO08xRptAcceleration::update_data(sh2_SensorValue_t* sensor_val)
{
    lock_user_data();
    data = sensor_val->un.accelerometer;
    data.accuracy = static_cast<BNO08xAccuracy>(sensor_val->status);
    unlock_user_data();

    if (rpt_bit & xEventGroupGetBits(sync_ctx->evt_grp_rpt_en))
        signal_data_available();
}

/**
 * @brief Grabs most recent acceleration data (including gravity), units are in m/s^2.
 *
 * @return Struct containing requested data.
 */
bno08x_accel_t BNO08xRptAcceleration::get()
{
    lock_user_data();
    bno08x_accel_t rqdata = data;
    unlock_user_data();
    return rqdata;
}