// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: imgxfer.proto

#ifndef PROTOBUF_imgxfer_2eproto__INCLUDED
#define PROTOBUF_imgxfer_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3001000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3001000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace imgxfer {
namespace proto {

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_imgxfer_2eproto();
void protobuf_InitDefaults_imgxfer_2eproto();
void protobuf_AssignDesc_imgxfer_2eproto();
void protobuf_ShutdownFile_imgxfer_2eproto();

class ImgXferMsg;
class Position;
class UiControl;

enum MsgType {
  IMG_XFER_START = 1,
  IMG_XFER_STOP = 2,
  IMG_XFER_UI = 3,
  IMG_XFER_ACK = 4,
  IMG_XFER_QUIT = 5
};
bool MsgType_IsValid(int value);
const MsgType MsgType_MIN = IMG_XFER_START;
const MsgType MsgType_MAX = IMG_XFER_QUIT;
const int MsgType_ARRAYSIZE = MsgType_MAX + 1;

const ::google::protobuf::EnumDescriptor* MsgType_descriptor();
inline const ::std::string& MsgType_Name(MsgType value) {
  return ::google::protobuf::internal::NameOfEnum(
    MsgType_descriptor(), value);
}
inline bool MsgType_Parse(
    const ::std::string& name, MsgType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<MsgType>(
    MsgType_descriptor(), name, value);
}
enum UiOption {
  MOUSE_CLICK = 1,
  RIGHT_CLICK = 2,
  DOUBLE_CLICK = 3,
  INPUT = 4
};
bool UiOption_IsValid(int value);
const UiOption UiOption_MIN = MOUSE_CLICK;
const UiOption UiOption_MAX = INPUT;
const int UiOption_ARRAYSIZE = UiOption_MAX + 1;

const ::google::protobuf::EnumDescriptor* UiOption_descriptor();
inline const ::std::string& UiOption_Name(UiOption value) {
  return ::google::protobuf::internal::NameOfEnum(
    UiOption_descriptor(), value);
}
inline bool UiOption_Parse(
    const ::std::string& name, UiOption* value) {
  return ::google::protobuf::internal::ParseNamedEnum<UiOption>(
    UiOption_descriptor(), name, value);
}
// ===================================================================

class Position : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:imgxfer.proto.Position) */ {
 public:
  Position();
  virtual ~Position();

  Position(const Position& from);

  inline Position& operator=(const Position& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Position& default_instance();

  static const Position* internal_default_instance();

  void Swap(Position* other);

  // implements Message ----------------------------------------------

  inline Position* New() const { return New(NULL); }

  Position* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Position& from);
  void MergeFrom(const Position& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Position* other);
  void UnsafeMergeFrom(const Position& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 x = 1;
  bool has_x() const;
  void clear_x();
  static const int kXFieldNumber = 1;
  ::google::protobuf::int32 x() const;
  void set_x(::google::protobuf::int32 value);

  // required int32 y = 2;
  bool has_y() const;
  void clear_y();
  static const int kYFieldNumber = 2;
  ::google::protobuf::int32 y() const;
  void set_y(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:imgxfer.proto.Position)
 private:
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::int32 x_;
  ::google::protobuf::int32 y_;
  friend void  protobuf_InitDefaults_imgxfer_2eproto_impl();
  friend void  protobuf_AddDesc_imgxfer_2eproto_impl();
  friend void protobuf_AssignDesc_imgxfer_2eproto();
  friend void protobuf_ShutdownFile_imgxfer_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<Position> Position_default_instance_;

// -------------------------------------------------------------------

class UiControl : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:imgxfer.proto.UiControl) */ {
 public:
  UiControl();
  virtual ~UiControl();

  UiControl(const UiControl& from);

  inline UiControl& operator=(const UiControl& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const UiControl& default_instance();

  static const UiControl* internal_default_instance();

  void Swap(UiControl* other);

  // implements Message ----------------------------------------------

  inline UiControl* New() const { return New(NULL); }

  UiControl* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UiControl& from);
  void MergeFrom(const UiControl& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(UiControl* other);
  void UnsafeMergeFrom(const UiControl& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .imgxfer.proto.UiOption option = 1;
  bool has_option() const;
  void clear_option();
  static const int kOptionFieldNumber = 1;
  ::imgxfer::proto::UiOption option() const;
  void set_option(::imgxfer::proto::UiOption value);

  // required uint32 sequence = 2;
  bool has_sequence() const;
  void clear_sequence();
  static const int kSequenceFieldNumber = 2;
  ::google::protobuf::uint32 sequence() const;
  void set_sequence(::google::protobuf::uint32 value);

  // optional .imgxfer.proto.Position position = 3;
  bool has_position() const;
  void clear_position();
  static const int kPositionFieldNumber = 3;
  const ::imgxfer::proto::Position& position() const;
  ::imgxfer::proto::Position* mutable_position();
  ::imgxfer::proto::Position* release_position();
  void set_allocated_position(::imgxfer::proto::Position* position);

  // optional string input = 4;
  bool has_input() const;
  void clear_input();
  static const int kInputFieldNumber = 4;
  const ::std::string& input() const;
  void set_input(const ::std::string& value);
  void set_input(const char* value);
  void set_input(const char* value, size_t size);
  ::std::string* mutable_input();
  ::std::string* release_input();
  void set_allocated_input(::std::string* input);

  // optional uint32 sleep_time = 5;
  bool has_sleep_time() const;
  void clear_sleep_time();
  static const int kSleepTimeFieldNumber = 5;
  ::google::protobuf::uint32 sleep_time() const;
  void set_sleep_time(::google::protobuf::uint32 value);

  // optional string resource = 6;
  bool has_resource() const;
  void clear_resource();
  static const int kResourceFieldNumber = 6;
  const ::std::string& resource() const;
  void set_resource(const ::std::string& value);
  void set_resource(const char* value);
  void set_resource(const char* value, size_t size);
  ::std::string* mutable_resource();
  ::std::string* release_resource();
  void set_allocated_resource(::std::string* resource);

  // optional bool ignored = 7;
  bool has_ignored() const;
  void clear_ignored();
  static const int kIgnoredFieldNumber = 7;
  bool ignored() const;
  void set_ignored(bool value);

  // @@protoc_insertion_point(class_scope:imgxfer.proto.UiControl)
 private:
  inline void set_has_option();
  inline void clear_has_option();
  inline void set_has_sequence();
  inline void clear_has_sequence();
  inline void set_has_position();
  inline void clear_has_position();
  inline void set_has_input();
  inline void clear_has_input();
  inline void set_has_sleep_time();
  inline void clear_has_sleep_time();
  inline void set_has_resource();
  inline void clear_has_resource();
  inline void set_has_ignored();
  inline void clear_has_ignored();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr input_;
  ::google::protobuf::internal::ArenaStringPtr resource_;
  ::imgxfer::proto::Position* position_;
  ::google::protobuf::uint32 sequence_;
  ::google::protobuf::uint32 sleep_time_;
  bool ignored_;
  int option_;
  friend void  protobuf_InitDefaults_imgxfer_2eproto_impl();
  friend void  protobuf_AddDesc_imgxfer_2eproto_impl();
  friend void protobuf_AssignDesc_imgxfer_2eproto();
  friend void protobuf_ShutdownFile_imgxfer_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<UiControl> UiControl_default_instance_;

// -------------------------------------------------------------------

class ImgXferMsg : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:imgxfer.proto.ImgXferMsg) */ {
 public:
  ImgXferMsg();
  virtual ~ImgXferMsg();

  ImgXferMsg(const ImgXferMsg& from);

  inline ImgXferMsg& operator=(const ImgXferMsg& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ImgXferMsg& default_instance();

  static const ImgXferMsg* internal_default_instance();

  void Swap(ImgXferMsg* other);

  // implements Message ----------------------------------------------

  inline ImgXferMsg* New() const { return New(NULL); }

  ImgXferMsg* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ImgXferMsg& from);
  void MergeFrom(const ImgXferMsg& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(ImgXferMsg* other);
  void UnsafeMergeFrom(const ImgXferMsg& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .imgxfer.proto.MsgType type = 1;
  bool has_type() const;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  ::imgxfer::proto::MsgType type() const;
  void set_type(::imgxfer::proto::MsgType value);

  // required uint32 id = 2;
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 2;
  ::google::protobuf::uint32 id() const;
  void set_id(::google::protobuf::uint32 value);

  // optional uint32 ack_value = 3;
  bool has_ack_value() const;
  void clear_ack_value();
  static const int kAckValueFieldNumber = 3;
  ::google::protobuf::uint32 ack_value() const;
  void set_ack_value(::google::protobuf::uint32 value);

  // optional .imgxfer.proto.UiControl ui = 4;
  bool has_ui() const;
  void clear_ui();
  static const int kUiFieldNumber = 4;
  const ::imgxfer::proto::UiControl& ui() const;
  ::imgxfer::proto::UiControl* mutable_ui();
  ::imgxfer::proto::UiControl* release_ui();
  void set_allocated_ui(::imgxfer::proto::UiControl* ui);

  // @@protoc_insertion_point(class_scope:imgxfer.proto.ImgXferMsg)
 private:
  inline void set_has_type();
  inline void clear_has_type();
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_ack_value();
  inline void clear_has_ack_value();
  inline void set_has_ui();
  inline void clear_has_ui();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::imgxfer::proto::UiControl* ui_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 ack_value_;
  int type_;
  friend void  protobuf_InitDefaults_imgxfer_2eproto_impl();
  friend void  protobuf_AddDesc_imgxfer_2eproto_impl();
  friend void protobuf_AssignDesc_imgxfer_2eproto();
  friend void protobuf_ShutdownFile_imgxfer_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<ImgXferMsg> ImgXferMsg_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Position

// required int32 x = 1;
inline bool Position::has_x() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Position::set_has_x() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Position::clear_has_x() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Position::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline ::google::protobuf::int32 Position::x() const {
  // @@protoc_insertion_point(field_get:imgxfer.proto.Position.x)
  return x_;
}
inline void Position::set_x(::google::protobuf::int32 value) {
  set_has_x();
  x_ = value;
  // @@protoc_insertion_point(field_set:imgxfer.proto.Position.x)
}

// required int32 y = 2;
inline bool Position::has_y() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Position::set_has_y() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Position::clear_has_y() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Position::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline ::google::protobuf::int32 Position::y() const {
  // @@protoc_insertion_point(field_get:imgxfer.proto.Position.y)
  return y_;
}
inline void Position::set_y(::google::protobuf::int32 value) {
  set_has_y();
  y_ = value;
  // @@protoc_insertion_point(field_set:imgxfer.proto.Position.y)
}

inline const Position* Position::internal_default_instance() {
  return &Position_default_instance_.get();
}
// -------------------------------------------------------------------

// UiControl

// required .imgxfer.proto.UiOption option = 1;
inline bool UiControl::has_option() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UiControl::set_has_option() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UiControl::clear_has_option() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UiControl::clear_option() {
  option_ = 1;
  clear_has_option();
}
inline ::imgxfer::proto::UiOption UiControl::option() const {
  // @@protoc_insertion_point(field_get:imgxfer.proto.UiControl.option)
  return static_cast< ::imgxfer::proto::UiOption >(option_);
}
inline void UiControl::set_option(::imgxfer::proto::UiOption value) {
  assert(::imgxfer::proto::UiOption_IsValid(value));
  set_has_option();
  option_ = value;
  // @@protoc_insertion_point(field_set:imgxfer.proto.UiControl.option)
}

// required uint32 sequence = 2;
inline bool UiControl::has_sequence() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UiControl::set_has_sequence() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UiControl::clear_has_sequence() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UiControl::clear_sequence() {
  sequence_ = 0u;
  clear_has_sequence();
}
inline ::google::protobuf::uint32 UiControl::sequence() const {
  // @@protoc_insertion_point(field_get:imgxfer.proto.UiControl.sequence)
  return sequence_;
}
inline void UiControl::set_sequence(::google::protobuf::uint32 value) {
  set_has_sequence();
  sequence_ = value;
  // @@protoc_insertion_point(field_set:imgxfer.proto.UiControl.sequence)
}

// optional .imgxfer.proto.Position position = 3;
inline bool UiControl::has_position() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void UiControl::set_has_position() {
  _has_bits_[0] |= 0x00000004u;
}
inline void UiControl::clear_has_position() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void UiControl::clear_position() {
  if (position_ != NULL) position_->::imgxfer::proto::Position::Clear();
  clear_has_position();
}
inline const ::imgxfer::proto::Position& UiControl::position() const {
  // @@protoc_insertion_point(field_get:imgxfer.proto.UiControl.position)
  return position_ != NULL ? *position_
                         : *::imgxfer::proto::Position::internal_default_instance();
}
inline ::imgxfer::proto::Position* UiControl::mutable_position() {
  set_has_position();
  if (position_ == NULL) {
    position_ = new ::imgxfer::proto::Position;
  }
  // @@protoc_insertion_point(field_mutable:imgxfer.proto.UiControl.position)
  return position_;
}
inline ::imgxfer::proto::Position* UiControl::release_position() {
  // @@protoc_insertion_point(field_release:imgxfer.proto.UiControl.position)
  clear_has_position();
  ::imgxfer::proto::Position* temp = position_;
  position_ = NULL;
  return temp;
}
inline void UiControl::set_allocated_position(::imgxfer::proto::Position* position) {
  delete position_;
  position_ = position;
  if (position) {
    set_has_position();
  } else {
    clear_has_position();
  }
  // @@protoc_insertion_point(field_set_allocated:imgxfer.proto.UiControl.position)
}

// optional string input = 4;
inline bool UiControl::has_input() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void UiControl::set_has_input() {
  _has_bits_[0] |= 0x00000008u;
}
inline void UiControl::clear_has_input() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void UiControl::clear_input() {
  input_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_input();
}
inline const ::std::string& UiControl::input() const {
  // @@protoc_insertion_point(field_get:imgxfer.proto.UiControl.input)
  return input_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UiControl::set_input(const ::std::string& value) {
  set_has_input();
  input_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:imgxfer.proto.UiControl.input)
}
inline void UiControl::set_input(const char* value) {
  set_has_input();
  input_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:imgxfer.proto.UiControl.input)
}
inline void UiControl::set_input(const char* value, size_t size) {
  set_has_input();
  input_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:imgxfer.proto.UiControl.input)
}
inline ::std::string* UiControl::mutable_input() {
  set_has_input();
  // @@protoc_insertion_point(field_mutable:imgxfer.proto.UiControl.input)
  return input_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UiControl::release_input() {
  // @@protoc_insertion_point(field_release:imgxfer.proto.UiControl.input)
  clear_has_input();
  return input_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UiControl::set_allocated_input(::std::string* input) {
  if (input != NULL) {
    set_has_input();
  } else {
    clear_has_input();
  }
  input_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), input);
  // @@protoc_insertion_point(field_set_allocated:imgxfer.proto.UiControl.input)
}

// optional uint32 sleep_time = 5;
inline bool UiControl::has_sleep_time() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void UiControl::set_has_sleep_time() {
  _has_bits_[0] |= 0x00000010u;
}
inline void UiControl::clear_has_sleep_time() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void UiControl::clear_sleep_time() {
  sleep_time_ = 0u;
  clear_has_sleep_time();
}
inline ::google::protobuf::uint32 UiControl::sleep_time() const {
  // @@protoc_insertion_point(field_get:imgxfer.proto.UiControl.sleep_time)
  return sleep_time_;
}
inline void UiControl::set_sleep_time(::google::protobuf::uint32 value) {
  set_has_sleep_time();
  sleep_time_ = value;
  // @@protoc_insertion_point(field_set:imgxfer.proto.UiControl.sleep_time)
}

// optional string resource = 6;
inline bool UiControl::has_resource() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void UiControl::set_has_resource() {
  _has_bits_[0] |= 0x00000020u;
}
inline void UiControl::clear_has_resource() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void UiControl::clear_resource() {
  resource_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_resource();
}
inline const ::std::string& UiControl::resource() const {
  // @@protoc_insertion_point(field_get:imgxfer.proto.UiControl.resource)
  return resource_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UiControl::set_resource(const ::std::string& value) {
  set_has_resource();
  resource_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:imgxfer.proto.UiControl.resource)
}
inline void UiControl::set_resource(const char* value) {
  set_has_resource();
  resource_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:imgxfer.proto.UiControl.resource)
}
inline void UiControl::set_resource(const char* value, size_t size) {
  set_has_resource();
  resource_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:imgxfer.proto.UiControl.resource)
}
inline ::std::string* UiControl::mutable_resource() {
  set_has_resource();
  // @@protoc_insertion_point(field_mutable:imgxfer.proto.UiControl.resource)
  return resource_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UiControl::release_resource() {
  // @@protoc_insertion_point(field_release:imgxfer.proto.UiControl.resource)
  clear_has_resource();
  return resource_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UiControl::set_allocated_resource(::std::string* resource) {
  if (resource != NULL) {
    set_has_resource();
  } else {
    clear_has_resource();
  }
  resource_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), resource);
  // @@protoc_insertion_point(field_set_allocated:imgxfer.proto.UiControl.resource)
}

// optional bool ignored = 7;
inline bool UiControl::has_ignored() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
inline void UiControl::set_has_ignored() {
  _has_bits_[0] |= 0x00000040u;
}
inline void UiControl::clear_has_ignored() {
  _has_bits_[0] &= ~0x00000040u;
}
inline void UiControl::clear_ignored() {
  ignored_ = false;
  clear_has_ignored();
}
inline bool UiControl::ignored() const {
  // @@protoc_insertion_point(field_get:imgxfer.proto.UiControl.ignored)
  return ignored_;
}
inline void UiControl::set_ignored(bool value) {
  set_has_ignored();
  ignored_ = value;
  // @@protoc_insertion_point(field_set:imgxfer.proto.UiControl.ignored)
}

inline const UiControl* UiControl::internal_default_instance() {
  return &UiControl_default_instance_.get();
}
// -------------------------------------------------------------------

// ImgXferMsg

// required .imgxfer.proto.MsgType type = 1;
inline bool ImgXferMsg::has_type() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ImgXferMsg::set_has_type() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ImgXferMsg::clear_has_type() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ImgXferMsg::clear_type() {
  type_ = 1;
  clear_has_type();
}
inline ::imgxfer::proto::MsgType ImgXferMsg::type() const {
  // @@protoc_insertion_point(field_get:imgxfer.proto.ImgXferMsg.type)
  return static_cast< ::imgxfer::proto::MsgType >(type_);
}
inline void ImgXferMsg::set_type(::imgxfer::proto::MsgType value) {
  assert(::imgxfer::proto::MsgType_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:imgxfer.proto.ImgXferMsg.type)
}

// required uint32 id = 2;
inline bool ImgXferMsg::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ImgXferMsg::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ImgXferMsg::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ImgXferMsg::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 ImgXferMsg::id() const {
  // @@protoc_insertion_point(field_get:imgxfer.proto.ImgXferMsg.id)
  return id_;
}
inline void ImgXferMsg::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:imgxfer.proto.ImgXferMsg.id)
}

// optional uint32 ack_value = 3;
inline bool ImgXferMsg::has_ack_value() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ImgXferMsg::set_has_ack_value() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ImgXferMsg::clear_has_ack_value() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ImgXferMsg::clear_ack_value() {
  ack_value_ = 0u;
  clear_has_ack_value();
}
inline ::google::protobuf::uint32 ImgXferMsg::ack_value() const {
  // @@protoc_insertion_point(field_get:imgxfer.proto.ImgXferMsg.ack_value)
  return ack_value_;
}
inline void ImgXferMsg::set_ack_value(::google::protobuf::uint32 value) {
  set_has_ack_value();
  ack_value_ = value;
  // @@protoc_insertion_point(field_set:imgxfer.proto.ImgXferMsg.ack_value)
}

// optional .imgxfer.proto.UiControl ui = 4;
inline bool ImgXferMsg::has_ui() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ImgXferMsg::set_has_ui() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ImgXferMsg::clear_has_ui() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ImgXferMsg::clear_ui() {
  if (ui_ != NULL) ui_->::imgxfer::proto::UiControl::Clear();
  clear_has_ui();
}
inline const ::imgxfer::proto::UiControl& ImgXferMsg::ui() const {
  // @@protoc_insertion_point(field_get:imgxfer.proto.ImgXferMsg.ui)
  return ui_ != NULL ? *ui_
                         : *::imgxfer::proto::UiControl::internal_default_instance();
}
inline ::imgxfer::proto::UiControl* ImgXferMsg::mutable_ui() {
  set_has_ui();
  if (ui_ == NULL) {
    ui_ = new ::imgxfer::proto::UiControl;
  }
  // @@protoc_insertion_point(field_mutable:imgxfer.proto.ImgXferMsg.ui)
  return ui_;
}
inline ::imgxfer::proto::UiControl* ImgXferMsg::release_ui() {
  // @@protoc_insertion_point(field_release:imgxfer.proto.ImgXferMsg.ui)
  clear_has_ui();
  ::imgxfer::proto::UiControl* temp = ui_;
  ui_ = NULL;
  return temp;
}
inline void ImgXferMsg::set_allocated_ui(::imgxfer::proto::UiControl* ui) {
  delete ui_;
  ui_ = ui;
  if (ui) {
    set_has_ui();
  } else {
    clear_has_ui();
  }
  // @@protoc_insertion_point(field_set_allocated:imgxfer.proto.ImgXferMsg.ui)
}

inline const ImgXferMsg* ImgXferMsg::internal_default_instance() {
  return &ImgXferMsg_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace imgxfer

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::imgxfer::proto::MsgType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::imgxfer::proto::MsgType>() {
  return ::imgxfer::proto::MsgType_descriptor();
}
template <> struct is_proto_enum< ::imgxfer::proto::UiOption> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::imgxfer::proto::UiOption>() {
  return ::imgxfer::proto::UiOption_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_imgxfer_2eproto__INCLUDED