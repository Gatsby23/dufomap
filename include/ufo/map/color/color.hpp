/*!
 * UFOMap: An Efficient Probabilistic 3D Mapping Framework That Embraces the Unknown
 *
 * @author Daniel Duberg (dduberg@kth.se)
 * @see https://github.com/UnknownFreeOccupied/ufomap
 * @version 1.0
 * @date 2022-05-13
 *
 * @copyright Copyright (c) 2022, Daniel Duberg, KTH Royal Institute of Technology
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Daniel Duberg, KTH Royal Institute of Technology
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *     list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef UFO_MAP_COLOR_HPP
#define UFO_MAP_COLOR_HPP

// UFO
#include <ufo/map/types.hpp>

// STL
#include <ostream>
#include <utility>

namespace ufo
{
/*!
 * @brief Color
 *
 */
struct Color {
	color_t blue{};
	color_t green{};
	color_t red{};

	constexpr Color() = default;

	constexpr Color(color_t red, color_t green, color_t blue)
	    : blue(blue), green(green), red(red)
	{
	}

	void swap(Color& other) noexcept
	{
		std::swap(blue, other.blue);
		std::swap(green, other.green);
		std::swap(red, other.red);
	}

	[[nodiscard]] constexpr bool isSet() const { return green || blue || red; }

	constexpr void clear() { blue = green = red = 0; }
};

constexpr bool operator==(Color const lhs, Color const rhs)
{
	return lhs.blue == rhs.blue && lhs.green == rhs.green && lhs.red == rhs.red;
}

constexpr bool operator!=(Color const lhs, Color const rhs) { return !(lhs == rhs); }
}  // namespace ufo

namespace std
{
inline ostream& operator<<(ostream& out, ufo::Color color)
{
	return out << "Red: " << +color.red << " Green: " << +color.green
	           << " Blue: " << +color.blue;
}

inline void swap(ufo::Color& lhs, ufo::Color& rhs) noexcept(noexcept(lhs.swap(rhs)))
{
	lhs.swap(rhs);
}
}  // namespace std

#endif  // UFO_MAP_COLOR_HPP
