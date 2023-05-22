#pragma once
#include <Arduino.h>

typedef void(*ramp_on_step_callback_t)(int value, void*state);

/// @brief Produces a ramp of values up or down
class ramp {
    // the last time the ramp updated
    uint32_t m_last_ts;
    // the step increment
    int m_step;
    // the remaining steps
    size_t m_count;
    // the time between steps, in ms
    uint32_t m_step_delay;
    // the current value
    int m_value;
    // the on_step callback
    ramp_on_step_callback_t m_on_step;
    // user state for the callback
    void* m_on_step_state;
public:
    /// @brief Constructs the ramp
    ramp();
    /// @brief Begin a ramp from a given value to a given value
    /// @param start The beginning value
    /// @param end The end value
    /// @param step The step value
    /// @param step_delay The delay between steps in milliseconds
    void begin_range(int start, int end, int step, uint32_t step_delay);
    /// @brief Begin a ramp from the given value for the specified count
    /// @param start The beginning value
    /// @param step The step value
    /// @param count The number of steps
    /// @param step_delay The delay between steps in milliseconds
    void begin(int start, int step, size_t count, uint32_t step_delay);
    /// @brief Sets the on_step callback 
    /// @param callback A callback of the form void(int,void*)
    /// @param state The state to pass
    void on_step(ramp_on_step_callback_t callback, void* state = nullptr);
    /// @brief The current value of the ramp
    /// @return The value
    int value() const;
    /// @brief Indicates if ramping is finished
    /// @return True if it's finished, otherwise false
    bool done() const;
    /// @brief Gives the ramp CPU slices. Should be called regularly.
    void update();
    /// @brief Indicates the computed step for this operation
    /// @return The current step being used. This may not be the same as the one passed in.
    int step() const;
    /// @brief Indicates the number of remaining advances to make
    /// @return The current number of steps remaining
    int remaining() const;
    /// @brief Indicates the current delay between steps
    /// @return The number of milliseconds that occur between steps
    uint32_t step_delay() const;
};