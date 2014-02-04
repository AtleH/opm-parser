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
                m_defaultApplied = false;
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

            const std::vector<T>& getValueList() const {
                return m_data;
            }

            T getSIValue(size_t index) const {
                assertSIData();
                {
                    if (index < m_data.size()) {
                        return m_SIdata[index];
                    } else
                        throw std::out_of_range("Out of range, index must be lower than " + boost::lexical_cast<std::string>(m_data.size()));
                }
            }

            const std::vector<T>& getSIValueList() const {
                assertSIData();
                return m_SIdata;
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

            void push_backDimension(std::shared_ptr<const Dimension> activeDimension , std::shared_ptr<const Dimension> defaultDimension) {
                if (m_defaultApplied)
                    m_dimensions.push_back( defaultDimension );
                else
                    m_dimensions.push_back( activeDimension );
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
            std::vector<T> m_data;
            std::vector<std::shared_ptr<const Dimension> > m_dimensions;
            // mutable is required because the data is "lazily" converted
            // to SI units in asserSIData() which needs to be callable by
            // 'const'-decorated methods
            mutable std::vector<T> m_SIdata;

            void assertSIData() const {
                if (m_dimensions.size() > 0) {
                    if (m_SIdata.size() > 0) {
                        // we already converted this item to SI!
                        return;
                    }
                    m_SIdata.resize( m_data.size() );
                    if (m_dimensions.size() == 1) {
                        double SIfactor = m_dimensions[0]->getSIScaling();
                        std::transform( m_data.begin() , m_data.end() , m_SIdata.begin() , std::bind1st(std::multiplies<double>(),SIfactor));
                    } else {
                        for (size_t index=0; index < m_data.size(); index++) {
                            size_t dimIndex = (index % m_dimensions.size());
                            double SIfactor = m_dimensions[dimIndex]->getSIScaling();
                            m_SIdata[index] = m_data[index] * SIfactor;
                        }
                    }
                } else
                    throw std::invalid_argument("No dimension has been set for item:" + name() + " can not ask for SI data");
            }

    };

    // http://stackoverflow.com/questions/26151/template-typedefs-whats-your-work-around

    template <typename T>
    struct DeckItemGenericPtr {
        typedef std::shared_ptr<DeckItemGeneric<T>> type;
    };

    template <typename T>
    struct DeckItemGenericConstPtr {
        typedef std::shared_ptr<const DeckItemGeneric<T>> type;
    };
}


#endif  /* DECKITEMGENERIC_HPP */

