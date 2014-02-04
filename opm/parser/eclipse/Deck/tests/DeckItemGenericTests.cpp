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

BOOST_AUTO_TEST_CASE(Int_Initialize) {
    BOOST_REQUIRE_NO_THROW(DeckItemGeneric<int> deckItem("TEST"));
}

BOOST_AUTO_TEST_CASE(Int_SetNameAndReadBack) {
    DeckItemGeneric<int> deckItem("TEST");
    BOOST_REQUIRE_EQUAL("TEST", deckItem.name());
}

BOOST_AUTO_TEST_CASE(Int_GetIntAtIndex_NoData_ExceptionThrown) {
    const DeckItemGeneric<int> deckItem("TEST");
    BOOST_CHECK_THROW(deckItem.getValue(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(Int_PushBack_VectorPushed_ElementsCorrect) {
    DeckItemGeneric<int> deckItem("TEST");
    std::deque<int> pushThese;
    pushThese.push_back(13);
    pushThese.push_back(33);
    deckItem.push_back(pushThese);
    BOOST_CHECK_EQUAL(13, deckItem.getValue(0));
    BOOST_CHECK_EQUAL(33, deckItem.getValue(1));
}

BOOST_AUTO_TEST_CASE(Int_PushBack_subVectorPushed_ElementsCorrect) {
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

BOOST_AUTO_TEST_CASE(Int_size_correct) {
    DeckItemGeneric<int> deckItem("TEST");

    BOOST_CHECK_EQUAL( 0U , deckItem.size());
    deckItem.push_back( 100 );
    BOOST_CHECK_EQUAL( 1U , deckItem.size());

    deckItem.push_back( 100 );
    deckItem.push_back( 100 );
    BOOST_CHECK_EQUAL( 3U , deckItem.size());
}

BOOST_AUTO_TEST_CASE(Int_DefaultApplied) {
    DeckItemGeneric<int> deckItem("TEST");
    BOOST_CHECK_EQUAL( false , deckItem.defaultApplied() );
    deckItem.push_backDefault( 1 );
    BOOST_CHECK_EQUAL( true , deckItem.defaultApplied() );
}

BOOST_AUTO_TEST_CASE(Int_PushBackMultiple) {
    DeckItemGeneric<int> item("HEI");
    item.push_backMultiple(10 , 100U );
    BOOST_CHECK_EQUAL( 100U , item.size() );
    for (size_t i=0; i < 100; i++)
        BOOST_CHECK_EQUAL(10 , item.getValue(i));
}


// ========= Tests of DeckItemGeneric<std::string>


BOOST_AUTO_TEST_CASE(String_InitializeString) {
    DeckItemGeneric<std::string> stringItem("TEST");
    BOOST_CHECK_EQUAL("TEST", stringItem.name());
}

BOOST_AUTO_TEST_CASE(String_GetStringAtIndex_NoData_ExceptionThrown) {
    const DeckItemGeneric<std::string> deckStringItem("TEST");
    BOOST_CHECK_THROW(deckStringItem.getValue(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(String_PushBack_VectorPushed_ElementsCorrect) {
    DeckItemGeneric<std::string> deckStringItem("TEST");
    std::deque<std::string> pushThese;
    pushThese.push_back("hei");
    pushThese.push_back("trygve-hei");
    deckStringItem.push_back(pushThese);
    BOOST_CHECK_EQUAL("hei", deckStringItem.getValue(0));
    BOOST_CHECK_EQUAL("trygve-hei", deckStringItem.getValue(1));
}

BOOST_AUTO_TEST_CASE(String_PushBack_subVectorPushed_ElementsCorrect) {
    DeckItemGeneric<std::string> deckStringItem("TEST");
    std::deque<std::string> pushThese;
    pushThese.push_back("Well-1");
    pushThese.push_back("Well-2");
    pushThese.push_back("Well-3");
    deckStringItem.push_back(pushThese, 2);
    BOOST_CHECK_EQUAL("Well-1", deckStringItem.getValue(0));
    BOOST_CHECK_EQUAL("Well-2", deckStringItem.getValue(1));
    BOOST_CHECK_EQUAL(2U, deckStringItem.size());
}

BOOST_AUTO_TEST_CASE(String_size_variouspushes_sizecorrect) {
    DeckItemGeneric<std::string> deckStringItem("TEST");

    BOOST_CHECK_EQUAL(0U, deckStringItem.size());
    deckStringItem.push_back("WELL-3");
    BOOST_CHECK_EQUAL(1U, deckStringItem.size());

    deckStringItem.push_back("WELL-4");
    deckStringItem.push_back("WELL-5");
    BOOST_CHECK_EQUAL(3U, deckStringItem.size());
}


BOOST_AUTO_TEST_CASE(String_DefaultApplied) {
    DeckItemGeneric<std::string> deckStringItem("TEST");
    BOOST_CHECK_EQUAL( false , deckStringItem.defaultApplied() );
    deckStringItem.push_backDefault( "1" );
    BOOST_CHECK_EQUAL( true , deckStringItem.defaultApplied() );
}


BOOST_AUTO_TEST_CASE(String_PushBackMultiple) {
    DeckItemGeneric<std::string> item("HEI");
    item.push_backMultiple("Heisann ", 100U );
    BOOST_CHECK_EQUAL( 100U , item.size() );
    for (size_t i=0; i < 100; i++)
        BOOST_CHECK_EQUAL("Heisann " , item.getValue(i));
}


// ========= Tests of DeckItemGeneric<double>


BOOST_AUTO_TEST_CASE(Double_InitializeDouble) {
    BOOST_REQUIRE_NO_THROW(DeckItemGeneric<double> deckDoubleItem("TEST"));
}

BOOST_AUTO_TEST_CASE(Double_GetDoubleAtIndex_NoData_ExceptionThrown) {
    const DeckItemGeneric<double> deckDoubleItem("TEST");
    BOOST_CHECK_THROW(deckDoubleItem.getValue(0), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(Double_PushBackDouble_VectorPushed_ElementsCorrect) {
    DeckItemGeneric<double> deckDoubleItem("TEST");
    std::deque<double> pushThese;
    pushThese.push_back(13);
    pushThese.push_back(33);
    deckDoubleItem.push_back(pushThese);
    BOOST_CHECK_EQUAL(13, deckDoubleItem.getValue(0));
    BOOST_CHECK_EQUAL(33, deckDoubleItem.getValue(1));
}

BOOST_AUTO_TEST_CASE(PushBackDouble_subVectorPushed_ElementsCorrect) {
    DeckItemGeneric<double> deckDoubleItem("TEST");
    std::deque<double> pushThese;
    pushThese.push_back(13);
    pushThese.push_back(33);
    pushThese.push_back(47);
    deckDoubleItem.push_back(pushThese , 2);
    BOOST_CHECK_EQUAL(13 , deckDoubleItem.getValue(0));
    BOOST_CHECK_EQUAL(33 , deckDoubleItem.getValue(1));
    BOOST_CHECK_EQUAL( 2U , deckDoubleItem.size());
}

BOOST_AUTO_TEST_CASE(Double_sizeDouble_correct) {
    DeckItemGeneric<double> deckDoubleItem("TEST");

    BOOST_CHECK_EQUAL( 0U , deckDoubleItem.size());
    deckDoubleItem.push_back( 100 );
    BOOST_CHECK_EQUAL( 1U , deckDoubleItem.size());

    deckDoubleItem.push_back( 100 );
    deckDoubleItem.push_back( 100 );
    BOOST_CHECK_EQUAL( 3U , deckDoubleItem.size());
}

BOOST_AUTO_TEST_CASE(Double_DefaultApplied) {
    DeckItemGeneric<double> deckDoubleItem("TEST");
    BOOST_CHECK_EQUAL( false , deckDoubleItem.defaultApplied() );
    deckDoubleItem.push_backDefault( 1 );
    BOOST_CHECK_EQUAL( true , deckDoubleItem.defaultApplied() );
}


BOOST_AUTO_TEST_CASE(Double_PushBackMultiple) {
    DeckItemGeneric<double> item("HEI");
    item.push_backMultiple(10.22 , 100 );
    BOOST_CHECK_EQUAL( 100U , item.size() );
    for (size_t i=0; i < 100; i++)
        BOOST_CHECK_EQUAL(10.22 , item.getValue(i));
}

BOOST_AUTO_TEST_CASE(Double_PushBackDimension) {
    DeckItemGeneric<double> item("HEI");
    std::shared_ptr<Dimension> activeDimension(new Dimension("L" , 100));
    std::shared_ptr<Dimension> defaultDimension(new Dimension("L" , 10));

    item.push_backDimension( activeDimension , defaultDimension);
}

//BOOST_AUTO_TEST_CASE(Double_PushBackDimensionInvalidType) {
//    DeckItemGeneric<int> item("HEI");
//    std::shared_ptr<Dimension> dim(new Dimension("L" , 100));
//    BOOST_CHECK_THROW( item.push_backDimension( dim , dim ) , std::invalid_argument );
//}

BOOST_AUTO_TEST_CASE(Double_GetSIWithoutDimensionThrows) {
    DeckItemGeneric<double> item("HEI");
    item.push_backMultiple(10.22 , 100 );

    BOOST_CHECK_THROW( item.getSIValue(0) , std::invalid_argument );
    BOOST_CHECK_THROW( item.getSIValueList( ) , std::invalid_argument );
}


BOOST_AUTO_TEST_CASE(GetSISingleDimensionCorrect) {
    DeckItemGeneric<double> item("HEI");
    std::shared_ptr<Dimension> dim(new Dimension("L" , 100));

    item.push_backMultiple(1 , 100 );
    item.push_backDimension( dim , dim );

    BOOST_CHECK_EQUAL( 1   , item.getValue(0) );
    BOOST_CHECK_EQUAL( 100 , item.getSIValue(0) );
}


BOOST_AUTO_TEST_CASE(GetSISingleDefault) {
    DeckItemGeneric<double> item("HEI");
    std::shared_ptr<Dimension> dim(new Dimension("L" , 1));
    std::shared_ptr<Dimension> defaultDim(new Dimension("L" , 100));

    item.push_backDefault(1 );
    item.push_backDimension( dim , defaultDim );

    BOOST_CHECK_EQUAL( 1   , item.getValue(0) );
    BOOST_CHECK_EQUAL( 100 , item.getSIValue(0) );
}


BOOST_AUTO_TEST_CASE(GetSIMultipleDim) {
    DeckItemGeneric<double> item("HEI");
    std::shared_ptr<Dimension> dim1(new Dimension("L" , 2));
    std::shared_ptr<Dimension> dim2(new Dimension("L" , 4));
    std::shared_ptr<Dimension> dim3(new Dimension("L" , 8));
    std::shared_ptr<Dimension> dim4(new Dimension("L" ,16));
    std::shared_ptr<Dimension> defaultDim(new Dimension("L" , 100));

    item.push_backMultiple( 1 , 16 );
    item.push_backDimension( dim1 , defaultDim );
    item.push_backDimension( dim2 , defaultDim );
    item.push_backDimension( dim3 , defaultDim );
    item.push_backDimension( dim4 , defaultDim );

    for (size_t i=0; i < 16; i+= 4) {
        BOOST_CHECK_EQUAL( 2   , item.getSIValue(i) );
        BOOST_CHECK_EQUAL( 4   , item.getSIValue(i+ 1) );
        BOOST_CHECK_EQUAL( 8   , item.getSIValue(i+2) );
        BOOST_CHECK_EQUAL(16   , item.getSIValue(i+3) );
    }
}

