/*
  Copyright 2013 Statoil ASA.

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DECKITEMGENERIC_HPP
#define DECKITEMGENERIC_HPP

#include <string>
#include <vector>
#include <deque>
#include <memory>
#include <boost/lexical_cast.hpp>

#include <opm/parser/eclipse/Deck/DeckItem.hpp>

namespace Opm {

    template <class T>
    class DeckItemGeneric {
        public:
            DeckItemGeneric(std::string name) {
                m_name = name;
            }

            const std::string& name() const {
                return m_name;
            }

            T getValue(size_t index) const {
                if (index < m_data.size()) {
                    return m_data[index];
                } else
                    throw std::out_of_range("Out of range, index must be lower than " + boost::lexical_cast<std::string>(m_data.size()));

            }

            void push_back(std::deque<T> data) {
                push_back(data, data.size());
            }

            void push_back(std::deque<T> data, size_t items) {
                for (size_t i = 0; i < items; i++) {
                    m_data.push_back(data[i]);
                }
            }

            void push_back(T data) {
                m_data.push_back(data);
            }

            void push_backDefault(T data) {
                m_data.push_back( data );
                m_defaultApplied = true;
            }

            void push_backMultiple(T value, size_t numValues) {
                for (size_t i = 0; i < numValues; i++)
                    m_data.push_back( value );
            }

            bool defaultApplied() const {
                return m_defaultApplied;
            }

            size_t size() const {
                return m_data.size();
            }
        private:
            bool m_defaultApplied;
            std::string m_name;
            std::vector<int> m_data;
    };

    //typedef std::shared_ptr<DeckItemGeneric<T>> DeckItemPtr<T>;
    //typedef std::shared_ptr<const DeckItemGeneric<T>> DeckItemConstPtr<T>;
}


#endif  /* DECKITEMGENERIC_HPP */

