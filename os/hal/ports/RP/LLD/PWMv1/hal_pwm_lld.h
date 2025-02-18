/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    hal_pwm_lld.h
 * @brief   PLATFORM PWM subsystem low level driver header.
 *
 * @addtogroup PWM
 * @{
 */

#ifndef HAL_PWM_LLD_H
#define HAL_PWM_LLD_H

#if (HAL_USE_PWM == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Number of PWM channels per PWM driver.
 */
#define PWM_CHANNELS                            2

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    PLATFORM configuration options
 * @{
 */
/**
 * @brief   PWMD0 driver enable switch.
 * @details If set to @p TRUE the support for PWM0 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(RP_PWM_USE_PWM0) || defined(__DOXYGEN__)
#define RP_PWM_USE_PWM0                  FALSE
#endif

/**
 * @brief   PWMD1 driver enable switch.
 * @details If set to @p TRUE the support for PWM1 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(RP_PWM_USE_PWM1) || defined(__DOXYGEN__)
#define RP_PWM_USE_PWM1                  FALSE
#endif

/**
 * @brief   PWMD2 driver enable switch.
 * @details If set to @p TRUE the support for PWM2 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(RP_PWM_USE_PWM2) || defined(__DOXYGEN__)
#define RP_PWM_USE_PWM2                  FALSE
#endif

/**
 * @brief   PWMD3 driver enable switch.
 * @details If set to @p TRUE the support for PWM3 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(RP_PWM_USE_PWM3) || defined(__DOXYGEN__)
#define RP_PWM_USE_PWM3                  FALSE
#endif

/**
 * @brief   PWMD4 driver enable switch.
 * @details If set to @p TRUE the support for PWM4 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(RP_PWM_USE_PWM4) || defined(__DOXYGEN__)
#define RP_PWM_USE_PWM4                  FALSE
#endif

/**
 * @brief   PWMD5 driver enable switch.
 * @details If set to @p TRUE the support for PWM5 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(RP_PWM_USE_PWM5) || defined(__DOXYGEN__)
#define RP_PWM_USE_PWM5                  FALSE
#endif

/**
 * @brief   PWMD6 driver enable switch.
 * @details If set to @p TRUE the support for PWM6 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(RP_PWM_USE_PWM6) || defined(__DOXYGEN__)
#define RP_PWM_USE_PWM6                  FALSE
#endif

/**
 * @brief   PWMD7 driver enable switch.
 * @details If set to @p TRUE the support for PWM7 is included.
 * @note    The default is @p FALSE.
 */
#if !defined(RP_PWM_USE_PWM7) || defined(__DOXYGEN__)
#define RP_PWM_USE_PWM7                  FALSE
#endif

/**
 * @brief   PWMD0..7 interrupt priority level setting.
 */
#if !defined(RP_PWM_IRQ_WRAP_NUMBER_PRIORITY) || defined(__DOXYGEN__)
#define RP_PWM_IRQ_WRAP_NUMBER_PRIORITY   3
#endif

/** @} */

/*===========================================================================*/
/* Configuration checks.                                                     */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a PWM mode.
 */
typedef uint32_t pwmmode_t;

/**
 * @brief   Type of a PWM channel.
 */
typedef uint8_t pwmchannel_t;

/**
 * @brief   Type of a channels mask.
 */
typedef uint32_t pwmchnmsk_t;

/**
 * @brief   Type of a PWM counter.
 */
typedef uint16_t pwmcnt_t;

/**
 * @brief   Type of a PWM driver channel configuration structure.
 */
typedef struct {
  /**
   * @brief Channel active logic level.
   */
  pwmmode_t                 mode;
  /**
   * @brief Channel callback pointer.
   * @note  This callback is invoked on the channel compare event. If set to
   *        @p NULL then the callback is disabled.
   */
  pwmcallback_t             callback;
  /* End of the mandatory fields.*/
} PWMChannelConfig;

/**
 * @brief   Type of a PWM driver configuration structure.
 */
typedef struct {
  /**
   * @brief   Timer clock in Hz.
   * @note    The low level can use assertions in order to catch invalid
   *          frequency specifications.
   */
  uint32_t                  frequency;
  /**
   * @brief   PWM period in ticks.
   * @note    The low level can use assertions in order to catch invalid
   *          period specifications.
   */
  pwmcnt_t                  period;
  /**
   * @brief Periodic callback pointer.
   * @note  This callback is invoked on PWM counter reset. If set to
   *        @p NULL then the callback is disabled.
   */
  pwmcallback_t             callback;
  /**
   * @brief Channels configurations.
   */
  PWMChannelConfig          channels[PWM_CHANNELS];
  /* End of the mandatory fields.*/
} PWMConfig;

/**
 * @brief   Structure representing a PWM driver.
 */
struct PWMDriver {
  /**
   * @brief Driver state.
   */
  pwmstate_t                state;
  /**
   * @brief Current driver configuration data.
   */
  const PWMConfig           *config;
  /**
   * @brief   Current PWM period in ticks.
   */
  pwmcnt_t                  period;
  /**
   * @brief   Mask of the enabled channels.
   */
  pwmchnmsk_t               enabled;
  /**
   * @brief   Number of channels in this instance.
   */
  pwmchannel_t              channels;
#if defined(PWM_DRIVER_EXT_FIELDS)
  PWM_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
  /**
   * @brief Pointer to the PWM registers block.
   */
  PWM_TypeDef               *pwm;

  /**
   * @brief Index of the associated PWM timer.
   */
  pwmchannel_t              timer_id;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Changes the period the PWM peripheral.
 * @details This function changes the period of a PWM unit that has already
 *          been activated using @p pwmStart().
 * @pre     The PWM unit must have been activated using @p pwmStart().
 * @post    The PWM unit period is changed to the new value.
 * @note    The function has effect at the next cycle start.
 * @note    If a period is specified that is shorter than the pulse width
 *          programmed in one of the channels then the behavior is not
 *          guaranteed.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] period    new cycle time in ticks
 *
 * @notapi
 */
#define pwm_lld_change_period(pwmp, period) \
  ((pwmp)->pwm->CH[(pwmp)->timer_id].TOP = (period))

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if (RP_PWM_USE_PWM0 == TRUE) && !defined(__DOXYGEN__)
extern PWMDriver PWMD0;
#endif

#if (RP_PWM_USE_PWM1 == TRUE) && !defined(__DOXYGEN__)
extern PWMDriver PWMD1;
#endif

#if (RP_PWM_USE_PWM2 == TRUE) && !defined(__DOXYGEN__)
extern PWMDriver PWMD2;
#endif

#if (RP_PWM_USE_PWM3 == TRUE) && !defined(__DOXYGEN__)
extern PWMDriver PWMD3;
#endif

#if (RP_PWM_USE_PWM4 == TRUE) && !defined(__DOXYGEN__)
extern PWMDriver PWMD4;
#endif

#if (RP_PWM_USE_PWM5 == TRUE) && !defined(__DOXYGEN__)
extern PWMDriver PWMD5;
#endif

#if (RP_PWM_USE_PWM6 == TRUE) && !defined(__DOXYGEN__)
extern PWMDriver PWMD6;
#endif

#if (RP_PWM_USE_PWM7 == TRUE) && !defined(__DOXYGEN__)
extern PWMDriver PWMD7;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void pwm_lld_init(void);
  void pwm_lld_start(PWMDriver *pwmp);
  void pwm_lld_stop(PWMDriver *pwmp);
  void pwm_lld_enable_channel(PWMDriver *pwmp,
                              pwmchannel_t channel,
                              pwmcnt_t width);
  void pwm_lld_disable_channel(PWMDriver *pwmp, pwmchannel_t channel);
  void pwm_lld_enable_periodic_notification(PWMDriver *pwmp);
  void pwm_lld_disable_periodic_notification(PWMDriver *pwmp);
  void pwm_lld_enable_channel_notification(PWMDriver *pwmp,
                                           pwmchannel_t channel);
  void pwm_lld_disable_channel_notification(PWMDriver *pwmp,
                                            pwmchannel_t channel);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_PWM == TRUE */

#endif /* HAL_PWM_LLD_H */

/** @} */
