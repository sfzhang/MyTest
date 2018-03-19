/**
 * @file Implement of ImgXferProto
 *
 * @author sfzhang
 * @date 2015-8-19
 */

#include "imgxferproto.h"

namespace imgxfer { namespace proto {

bool ImgXferProto::size(size_t &s) const
{
    int size = m_msg.ByteSize();
    if (size <= 0) {
        return false;
    }

    s = static_cast<size_t>(size);
    return true;
}

bool ImgXferProto::parse(const char *data, std::size_t size)
{
    if (m_msg.ParseFromArray(data, static_cast<int>(size))) {
        return true;
    }

    return false;

}

bool ImgXferProto::serialize(char *data, std::size_t size)
{
    if (m_msg.SerializeToArray(data, static_cast<int>(size))) {
        return true;
    }
    return false;
}

} }
