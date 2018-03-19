/**
 * @file Image transfer protocol
 *
 * @author sfzhang
 * @date 2015-8-18
 */

#ifndef IMGXFERPROTO_H
#define IMGXFERPROTO_H

#include <cstddef>
#include "imgxfer.pb.h"
#include "errorcode.h"

namespace imgxfer { namespace proto {

/**
 * @class ImgXferProto
 */
class ImgXferProto {

public:

    /**
     * @brief Clear
     */
    void clear()
    {
        m_msg.Clear();
    }

    /**
     * @brief Prepare to start
     */
    void start()
    {
        clear();
        m_msg.set_type(IMG_XFER_START);
    }

    /**
     * @brief Prepare to stop
     */
    void stop()
    {
        clear();
        m_msg.set_type(IMG_XFER_STOP);
    }

    /**
     * @brief Prepare to ack
     * @param[in] id The message id
     * @param[in] value The ack value
     */
    void ack(uint32_t id, uint32_t value)
    {
        clear();
        m_msg.set_type(IMG_XFER_ACK);
        m_msg.set_id(id);
        m_msg.set_ack_value(value);
    }

    /**
     * @brief Get the message type
     * @return Message type
     */
    MsgType type() const
    {
        return m_msg.type();
    }

    /**
     * @brief Get the message ID
     * @return Message ID
     */
    uint32_t id() const
    {
        return m_msg.id();
    }

    /**
     * @brief Check has UI
     *
     * @return true if has UI, otherwise false
     */
    bool hasUi() const
    {
        return m_msg.has_ui();
    }

    /**
     * @brief Get UI control
     *
     * @return UI control
     */
    const UiControl &ui() const
    {
        return m_msg.ui();
    }

    /**
     * @brief Get size of ImgXferMsg
     *
     * @param[out] s The size of ImgXferMsg
     *
     * @return true if success, otherwise false
     */
    bool size(std::size_t &s) const;

    /** 
     * @brief Parse a protocol buffer contained in an array of bytes
     *
     * @param[in] data The buffer to be parsed
     * @param[in] size The size of buffer
     *
     * @return true if success to parse, otherwise false
     */
    bool parse(const char *data, std::size_t size);

    /** 
     * @brief Serialize the message and store it in the given byte array
     *
     * @param[in] data The buffer saved the message
     * @param[in] size The size of buffer
     *
     * @return true if success to serialize, otherwise false
     */
    bool serialize(char *data, std::size_t size);

protected:

    ImgXferMsg m_msg;  /* The image transfer msg */

};

} };

#endif
