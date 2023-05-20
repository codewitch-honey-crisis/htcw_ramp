#pragma once
#include <Arduino.h>

typedef void(*ramp_on_step_callback_t)(int value, void*state);

class ramp {
    uint32_t m_last_ts;
    int m_step;
    size_t m_count;
    uint32_t m_step_delay;
    int m_value;
    ramp_on_step_callback_t m_on_step;
    void* m_on_step_state;
public:
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
};