
#include <Util/Endian.h>

#include "OutputStream.hpp"
#include "RawOutputStream.hpp"
#include "FileOutputStream.hpp"

using Util::MaybePointer;

namespace IOStream {

using std::string;

OutputStream::OutputStream(const MaybePointer<RawOutputStream> &raw, Endian endian)
:raw(raw) {
    if (endian == NATIVE) {
        swap = false;
    }
    else {
        swap = bigEndian ? (endian == LITTLE) : (endian == BIG);
    }
}

OutputStream::OutputStream(const std::string &filename)
:OutputStream(new FileOutputStream(filename)) {}

OutputStream::OutputStream(int fd)
:OutputStream(new FileOutputStream(fd)) {}

OutputStream & OutputStream::operator<<(int8_t data) {
    raw->write(&data, sizeof(data));
    return *this;
}

OutputStream & OutputStream::operator<<(uint8_t data) {
    raw->write(&data, sizeof(data));
    return *this;
}

OutputStream & OutputStream::operator<<(int16_t data) {
    if (swap) {
        swapEndian(data);
    }
    raw->write(&data, sizeof(data));
    return *this;
}

OutputStream & OutputStream::operator<<(uint16_t data) {
    if (swap) {
        swapEndian(data);
    }
    raw->write(&data, sizeof(data));
    return *this;
}

OutputStream & OutputStream::operator<<(int32_t data) {
    if (swap) {
        swapEndian(data);
    }
    raw->write(&data, sizeof(data));
    return *this;
}

OutputStream & OutputStream::operator<<(uint32_t data) {
    if (swap) {
        swapEndian(data);
    }
    raw->write(&data, sizeof(data));
    return *this;
}

OutputStream & OutputStream::operator<<(int64_t data) {
    if (swap) {
        swapEndian(data);
    }
    raw->write(&data, sizeof(data));
    return *this;
}

OutputStream & OutputStream::operator<<(uint64_t data) {
    if (swap) {
        swapEndian(data);
    }
    raw->write(&data, sizeof(data));
    return *this;
}

OutputStream & OutputStream::operator<<(float data) {
    if (swap) {
        swapEndian(data);
    }
    raw->write(&data, sizeof(data));
    return *this;
}

OutputStream & OutputStream::operator<<(double data) {
    if (swap) {
        swapEndian(data);
    }
    raw->write(&data, sizeof(data));
    return *this;
}

OutputStream & OutputStream::operator<<(const std::string &data) {
    uint16_t length(data.size());
    operator<<(length);
    raw->write(&data[0], length);
    return *this;
}

void OutputStream::writeByte(int8_t data) {
    operator<<(data);
}

void OutputStream::writeUByte(uint8_t data) {
    operator<<(data);
}

void OutputStream::writeShort(int16_t data) {
    operator<<(data);
}

void OutputStream::writeUShort(uint16_t data) {
    operator<<(data);
}

void OutputStream::writeInt(int32_t data) {
    operator<<(data);
}

void OutputStream::writeUInt(uint32_t data) {
    operator<<(data);
}

void OutputStream::writeLong(int64_t data) {
    operator<<(data);
}

void OutputStream::writeULong(uint64_t data) {
    operator<<(data);
}

void OutputStream::writeFloat(float data) {
    operator<<(data);
}

void OutputStream::writeDouble(double data) {
    operator<<(data);
}

void OutputStream::writeString(const string &data) {
    operator<<(data);
}

ssize_t OutputStream::write(const void *buf, size_t length) {
    return raw->write(buf, length);
}

off_t OutputStream::seek(off_t offset, int whence) {
    return raw->seek(offset, whence);
}

void OutputStream::close() {
    raw->close();
}


OutputStream::~OutputStream() {
}

}

