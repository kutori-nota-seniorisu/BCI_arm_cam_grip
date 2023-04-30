// Auto-generated. Do not edit!

// (in-package visp_ros.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class ImagePoint {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.i = null;
      this.j = null;
    }
    else {
      if (initObj.hasOwnProperty('i')) {
        this.i = initObj.i
      }
      else {
        this.i = 0.0;
      }
      if (initObj.hasOwnProperty('j')) {
        this.j = initObj.j
      }
      else {
        this.j = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ImagePoint
    // Serialize message field [i]
    bufferOffset = _serializer.float64(obj.i, buffer, bufferOffset);
    // Serialize message field [j]
    bufferOffset = _serializer.float64(obj.j, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ImagePoint
    let len;
    let data = new ImagePoint(null);
    // Deserialize message field [i]
    data.i = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [j]
    data.j = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'visp_ros/ImagePoint';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '600c777d3f6d5d378f3fc5f8df469dbe';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # Message corresponding to vpImagePoint class
    float64 i      # i (respectively v) position in the image
    float64 j      # j (respectively u) position in the image
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ImagePoint(null);
    if (msg.i !== undefined) {
      resolved.i = msg.i;
    }
    else {
      resolved.i = 0.0
    }

    if (msg.j !== undefined) {
      resolved.j = msg.j;
    }
    else {
      resolved.j = 0.0
    }

    return resolved;
    }
};

module.exports = ImagePoint;
