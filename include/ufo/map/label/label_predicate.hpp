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

#ifndef UFO_MAP_LABEL_PREDICATE_HPP
#define UFO_MAP_LABEL_PREDICATE_HPP

// UFO
#include <ufo/map/label/label_map.hpp>
#include <ufo/map/node.hpp>
#include <ufo/map/predicate/predicate.hpp>
#include <ufo/map/types.hpp>

namespace ufo::pred
{
//
// LabelMap
//

struct LabelMap {
};

template <>
struct ValueCheck<LabelMap> {
	using Pred = LabelMap;

	template <class Map>
	static constexpr bool apply(Pred, Map const&, Node)
	{
		return IsLabelMap<Map>;
	}
};

template <class PredPost>
struct ValueCheck<THEN<LabelMap, PredPost>> {
	using Pred = THEN<LabelMap, PredPost>;

	template <class Map, class Node>
	static constexpr bool apply(Pred const& p, Map const& m, Node const& n)
	{
		if constexpr (ValueCheck<LabelMap>::apply(p.pre, m, n)) {
			return ValueCheck<PredPost>::apply(p.post, m, n);
		} else {
			return true;
		}
	}
};

template <>
struct InnerCheck<LabelMap> {
	using Pred = LabelMap;

	template <class Map>
	static constexpr bool apply(Pred, Map const&, Node)
	{
		return IsLabelMap<Map>;
	}
};

template <class PredPost>
struct InnerCheck<THEN<LabelMap, PredPost>> {
	using Pred = THEN<LabelMap, PredPost>;

	template <class Map, class Node>
	static constexpr bool apply(Pred const& p, Map const& m, Node const& n)
	{
		if constexpr (InnerCheck<LabelMap>::apply(p.pre, m, n)) {
			return InnerCheck<PredPost>::apply(p.post, m, n);
		} else {
			return true;
		}
	}
};

//
// Label
//

template <bool Negated = false>
struct Label {
	constexpr Label(label_t label) : label(label) {}

	label_t label;
};

template <bool Negated>
constexpr Label<!Negated> operator!(Label<Negated> p)
{
	return Label<!Negated>(p.label);
}

template <bool Negated>
struct ValueCheck<Label<Negated>> {
	using Pred = Label<Negated>;

	template <class Map>
	static inline bool apply(Pred p, Map const& m, Node n)
	{
		if constexpr (Negated) {
			return p.label != m.label(n.index());
		} else {
			return p.label == m.label(n.index());
		}
	}
};

template <bool Negated>
struct InnerCheck<Label<Negated>> {
	using Pred = Label<Negated>;

	template <class Map>
	static inline bool apply(Pred p, Map const& m, Node n)
	{
		if constexpr (Negated) {
			return true;  // FIXME: Can this be better?
		} else {
			return p.label == (m.label(n.index()) & p.label);
		}
	}
};

}  // namespace ufo::pred

#endif  // UFO_MAP_LABEL_PREDICATE_HPP