#ifndef __DARKRL__BITMAP_HPP__
#define __DARKRL__BITMAP_HPP__

#include <future>
#include <memory>

#include "Semaphore.hpp"
#include "Types.hpp"
#include "Vector.hpp"

class Bitmap
{
public:
    Bitmap( const char* fn );
    Bitmap( const v2i& size );
    ~Bitmap();

    void Write( const char* fn );

    uint32* Data() { if( m_load.valid() ) m_load.wait(); return m_data; }
    const uint32* Data() const { if( m_load.valid() ) m_load.wait(); return m_data; }
    const v2i& Size() const { return m_size; }
    bool Alpha() const { return m_alpha; }

private:
    uint32* m_data;
    v2i m_size;
    bool m_alpha;
    Semaphore m_sema;
    std::future<void> m_load;
};

typedef std::shared_ptr<Bitmap> BitmapPtr;

#endif
