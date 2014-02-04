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


#define BOOST_TEST_MODULE DeckItemTests

#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include <opm/parser/eclipse/Deck/DeckItemGeneric.hpp>

using namespace Opm;

// ========= Tests of DeckItemGeneric<int>

BOOST_AUTO_TEST_CASE(Initialize) {
    BOOST_REQUIRE_NO_THROW(DeckItemGeneric<int> deckItem("TEST"));
}

BOOST_AUTO_TEST_CASE(SetNameAndReadBack) {
    DeckItemGeneric<int> deckItem("TEST");
    BOOST_REQUIRE_EQUAL("TEST", deckItem.name());
}

BOOST_AUTO_TEST_CASE(GetIntAtIndex_NoData_ExceptionThrown) {
    const DeckItemGeneric<int> deckItem("TEST");
    BOOST_CHECK_THROW(deckItem.getValue(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(PushBack_VectorPushed_ElementsCorrect) {
    DeckItemGeneric<int> deckItem("TEST");
    std::deque<int> pushThese;
    pushThese.push_back(13);
    pushThese.push_back(33);
    deckItem.push_back(pushThese);
    BOOST_CHECK_EQUAL(13, deckItem.getValue(0));
    BOOST_CHECK_EQUAL(33, deckItem.getValue(1));
}

BOOST_AUTO_TEST_CASE(PushBack_subVectorPushed_ElementsCorrect) {
    DeckItemGeneric<int> deckItem("TEST");
    std::deque<int> pushThese;
    pushThese.push_back(13);
    pushThese.push_back(33);
    pushThese.push_back(47);
    deckItem.push_back(pushThese , 2);
    BOOST_CHECK_EQUAL(13 , deckItem.getValue(0));
    BOOST_CHECK_EQUAL(33 , deckItem.getValue(1));
    BOOST_CHECK_EQUAL( 2U , deckItem.size());
}

BOOST_AUTO_TEST_CASE(size_correct) {
    DeckItemGeneric<int> deckItem("TEST");

    BOOST_CHECK_EQUAL( 0U , deckItem.size());
    deckItem.push_back( 100 );
    BOOST_CHECK_EQUAL( 1U , deckItem.size());

    deckItem.push_back( 100 );
    deckItem.push_back( 100 );
    BOOST_CHECK_EQUAL( 3U , deckItem.size());
}

BOOST_AUTO_TEST_CASE(DefaultApplied) {
    DeckItemGeneric<int> deckItem("TEST");
    BOOST_CHECK_EQUAL( false , deckItem.defaultApplied() );
    deckItem.push_backDefault( 1 );
    BOOST_CHECK_EQUAL( true , deckItem.defaultApplied() );
}

BOOST_AUTO_TEST_CASE(PushBackMultiple) {
    DeckItemGeneric<int> item("HEI");
    item.push_backMultiple(10 , 100U );
    BOOST_CHECK_EQUAL( 100U , item.size() );
    for (size_t i=0; i < 100; i++)
        BOOST_CHECK_EQUAL(10 , item.getValue(i));
}

