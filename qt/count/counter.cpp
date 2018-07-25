#include "counter.h"

void Counter::setValue(int value)
{
    if (m_value != value) {
        m_value = value;
        emit valueChanged(value);
    }
}
