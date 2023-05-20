#include <ramp.hpp>

ramp::ramp() : m_count(0),m_value(0),m_step(1),m_step_delay(10), m_on_step(nullptr),m_on_step_state(nullptr) {

}
void ramp::begin(int start, int step, size_t count, uint32_t step_delay) {
    m_step = step;
    m_count = count;
    m_step_delay = step_delay;
    m_value = start;
    m_last_ts = 0;
}
void ramp::begin_range(int start, int end, int step, uint32_t step_delay) {
    int astep = abs(step);
    int cstep = start>end?-astep:step;
    size_t count = (abs(end-start)+1)/astep;
    begin(start,cstep,count,step_delay);
}
void ramp::on_step(ramp_on_step_callback_t callback, void* state) {
    m_on_step = callback;
    m_on_step_state = state;
}
void ramp::update() {
    if(m_count>0) {
        if(m_last_ts == 0) {
            m_last_ts = millis();
            if(m_on_step!=nullptr) {
                m_on_step(m_value,m_on_step_state);
            }
            --m_count;
        } else if(millis()>m_last_ts+m_step_delay) {
            m_last_ts = millis();
            m_value+=m_step;
            if(m_on_step!=nullptr) {
                m_on_step(m_value,m_on_step_state);
            }
            --m_count;
        }
    }
}
int ramp::value() const {
    return m_value;
}
bool ramp::done() const {
    return m_count <= 0;
}