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

#define BOOST_TEST_MODULE ParserIntegrationTestsInternalData

#include <stdexcept>
#include <iostream>
#include <boost/filesystem.hpp>

#include <boost/test/unit_test.hpp>

#include <opm/parser/eclipse/Parser/Parser.hpp>
#include <opm/parser/eclipse/Parser/ParserKeyword.hpp>
#include <opm/parser/eclipse/Deck/Deck.hpp>

#include <opm/parser/eclipse/EclipseState/Schedule/Schedule.hpp>
#include <opm/parser/eclipse/EclipseState/Schedule/GroupTree.hpp>

using namespace Opm;

//NOTE: needs statoil dataset

BOOST_AUTO_TEST_CASE(ParseFileWithManyKeywords) {
    boost::filesystem::path multipleKeywordFile("testdata/statoil/gurbat_trimmed.DATA");

    ParserPtr parser(new Parser());
    DeckPtr deck =  parser->parseFile(multipleKeywordFile.string() , false);
    SchedulePtr schedule(new Schedule(deck));
    
    GroupTreePtr treeAtStart = schedule->getGroupTree(0);
    GroupTreeNodePtr fieldNode = treeAtStart->getNode("FIELD");
    BOOST_CHECK(fieldNode);
    BOOST_CHECK(fieldNode->getChildGroup("OP"));
    BOOST_CHECK(fieldNode->getChildGroup("WI"));
}
