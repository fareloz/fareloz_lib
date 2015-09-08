#pragma once

#include <string>
#include <vector>

#include "common.hpp"

namespace fareloz
{
    namespace string
    {
        template<typename T>
        class tokenizer
        {
        public:
            typedef typename T::value_type delimiter_type;

            tokenizer(const T& str, delimiter_type delimiter = ' ')
            {
                m_tokens = split(str, delimiter);
            }

            virtual ~tokenizer() { }

            inline size_t size() { return m_tokens.size(); }
            inline const T& operator[](size_t index) { return m_tokens[index]; }
            inline std::vector<T>& tokens() { return m_tokens; }

        private:
            std::vector<T> m_tokens;
        };

        typedef tokenizer<std::wstring> w_tokenizer;
        typedef tokenizer<std::string> a_tokenizer;

    }
}