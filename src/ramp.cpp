#include <ramp.hpp>

/// @brief Constructs the ramp
ramp::ramp() : m_count(0),m_value(0),m_step(1),m_step_delay(10), m_on_step(nullptr),m_on_step_state(nullptr) {

}
/// @brief Begin a ramp from the given value for the specified count
/// @param start The beginning value
/// @param step The step value
/// @param count The number of steps
/// @param step_delay The delay between steps in milliseconds
void ramp::begin(int start, int step, size_t count, uint32_t step_delay) {
    m_step = step;
    m_count = count;
    m_step_delay = step_delay;
    m_value = start;
    m_last_ts = 0;
}
/// @brief Begin a ramp from a given value to a given value
/// @param start The beginning value
/// @param end The end value
/// @param step The step value
/// @param step_delay The delay between steps in milliseconds
void ramp::begin_range(int start, int end, int step, uint32_t step_delay) {
    int astep = abs(step);
    int cstep = start>end?-astep:step;
    size_t count = (abs(end-start)+1)/astep;
    begin(start,cstep,count,step_delay);
}
/// @brief Sets the on_step callback 
/// @param callback A callback of the form void(int,void*)
/// @param state The state to pass
void ramp::on_step(ramp_on_step_callback_t callback, void* state) {
    m_on_step = callback;
    m_on_step_state = state;
}
/// @brief Gives the ramp CPU slices. Should be called regularly.
void ramp::update() {
    if(m_count>0) {
        uint32_t current_ts = millis();
        if(m_last_ts == 0) {
            m_last_ts = current_ts;
            if(m_on_step!=nullptr) {
                m_on_step(m_value,m_on_step_state);
            }
            --m_count;
        } else if(current_ts>m_last_ts+m_step_delay) {
            m_last_ts = current_ts;
            m_value+=m_step;
            if(m_on_step!=nullptr) {
                m_on_step(m_value,m_on_step_state);
            }
            --m_count;
        }
    }
}
/// @brief The current value of the ramp
/// @return The value
int ramp::value() const {
    return m_value;
}
/// @brief Indicates if ramping is finished
/// @return True if it's finished, otherwise false
bool ramp::done() const {
    return m_count <= 0;
}