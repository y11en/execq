/*
 * MIT License
 *
 * Copyright (c) 2018 Alkenso (Vladimir Vashurkin)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "CancelTokenProvider.h"

execq::impl::CancelToken execq::impl::CancelTokenProvider::token()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_currentToken;
}

void execq::impl::CancelTokenProvider::cancel()
{
    cancelAndRenew(false);
}

void execq::impl::CancelTokenProvider::cancelAndRenew()
{
    cancelAndRenew(true);
}

void execq::impl::CancelTokenProvider::cancelAndRenew(const bool renew)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_currentToken)
    {
        *m_currentToken = true;
    }
    if (renew)
    {
        m_currentToken = std::make_shared<std::atomic_bool>(false);
    }
}
