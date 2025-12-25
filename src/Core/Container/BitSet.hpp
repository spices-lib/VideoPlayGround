#pragma once
#include "Core/Core.h"

#include <bitset>
#include <shared_mutex>

namespace PlayGround {

    template<typename T>
    class BitSet
    {
    public:

        using TSize = std::underlying_type_t<T>;

    private:

        std::bitset<static_cast<size_t>(T::Count)> m_Bits{};
        mutable std::shared_mutex m_Mutex;

    public:


        BitSet() = default;
        virtual ~BitSet() = default;


        BitSet(const BitSet& other)
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits = other.m_Bits;
        }

        BitSet& operator=(const BitSet& other)
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits = other.m_Bits;

            return *this;
        }

        BitSet(BitSet&& other) noexcept
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits = std::move(other.m_Bits);
        }

        BitSet& operator=(BitSet&& other) noexcept
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits = std::move(other.m_Bits);

            return *this;
        }

        BitSet operator|(const BitSet& other) const
        {
            std::shared_lock<std::shared_mutex> lock(m_Mutex);

            BitSet result;

            result.m_Bits = m_Bits | other.m_Bits;

            return result;
        }

        BitSet operator&(const BitSet& other) const
        {
            std::shared_lock<std::shared_mutex> lock(m_Mutex);

            BitSet result;

            result.m_Bits = m_Bits & other.m_Bits;

            return result;
        }

        BitSet& operator|=(const BitSet& other)
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits |= other.m_Bits;

            return *this;
        }

        BitSet& operator&=(const BitSet& other)
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits &= other.m_Bits;

            return *this;
        }

        bool operator==(const BitSet& other) const
        {
            std::shared_lock<std::shared_mutex> lock(m_Mutex);

            return m_Bits == other.m_Bits;
        }

        bool operator!=(const BitSet& other) const
        {
            std::shared_lock<std::shared_mutex> lock(m_Mutex);

            return m_Bits != other.m_Bits;
        }

        explicit operator TSize() const
        {
            std::shared_lock<std::shared_mutex> lock(m_Mutex);

            return static_cast<TSize>(m_Bits.to_ulong());
        }

        void Set(T bit, bool value)
        {
            if (bit == T::Count)
            {
                Reset();

                if (value)
                {
                    Flip();
                }
            }
            else 
            {
                std::unique_lock<std::shared_mutex> lock(m_Mutex);

                m_Bits.set(static_cast<size_t>(static_cast<TSize>(bit)), value);
            }
        }

        bool Test(T bit) const
        {
            if (bit == T::Count)
            {
                return !None();
            }
            else
            {
                std::shared_lock<std::shared_mutex> lock(m_Mutex);

                return m_Bits.test(static_cast<size_t>(static_cast<TSize>(bit)));
            }
        }

        void Reset()
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits.reset();
        }

        void Reset(T bit)
        {
            if (bit == T::Count)
            {
                Reset();
            }
            else
            {
                std::unique_lock<std::shared_mutex> lock(m_Mutex);

                m_Bits.reset(static_cast<size_t>(static_cast<TSize>(bit)));
            }
        }

        void Flip()
        {
            std::unique_lock<std::shared_mutex> lock(m_Mutex);

            m_Bits.flip();
        }

        void Flip(T bit)
        {
            if (bit == T::Count)
            {
                Flip();
            }
            else
            {
                std::unique_lock<std::shared_mutex> lock(m_Mutex);

                m_Bits.flip(static_cast<size_t>(static_cast<TSize>(bit)));
            }
        }

        bool Any() const
        {
            std::shared_lock<std::shared_mutex> lock(m_Mutex);

            return m_Bits.any();
        }

        bool None() const
        {
            std::shared_lock<std::shared_mutex> lock(m_Mutex);

            return m_Bits.none();
        }

    };

}
