/***************************************************************************
 *   Copyright (C) 2010 Fernando Jiménez Moreno <ferjmoreno@gmail.com>     *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef QTGDATAATOMFEED_H
#define QTGDATAATOMFEED_H

#include <ostream>

/*atom*/
class Author
{
public:
    QString name;
    QString email;
    QUrl uri;
};

class Link
{
public:
    QString rel;
    QString type;
    QUrl href;
};

class Category
{
public:
    QUrl scheme;
    QString term;        
};

class Content
{
public:
    QByteArray content;
    QString type;
};

class Generator
{
public:
    QString version;
    QUrl uri;
    QString generator;
};

/**
   From http://www.ietf.org/rfc/rfc4287.txt
   The "atom:entry" element represents an individual entry, acting as a
   container for metadata and data associated with the entry.  This
   element can appear as a child of the atom:feed element, or it can
   appear as the document (i.e., top-level) element of a stand-alone
   Atom Entry Document.

   atomEntry =
      element atom:entry {
         atomCommonAttributes,
         (atomAuthor*
          & atomCategory*
          & atomContent?
          & atomContributor*
          & atomId
          & atomLink*
          & atomPublished?
          & atomRights?
          & atomSource?
          & atomSummary?
          & atomTitle
          & atomUpdated
          & extensionElement*)
      }

 */

class AtomEntry
{
public:
    QString id;
    QString title;
    QString summary;
    QList<Author> authors;
    QDateTime published;
    QDateTime updated;    
    QList<Link> links;
    QList<Category> categories;    
    Content content;
    QString rights;

    virtual ~AtomEntry(){};

    friend std::ostream& operator<< (std::ostream &out,AtomEntry &atomEntry) {
        out << "Entry: \n" << "\t id: " << atomEntry.id.toAscii().data() <<
               "\n\t title: " << atomEntry.title.toAscii().data() <<               
               "\n\t QString summary: " << atomEntry.summary.toAscii().data();
        return out;
    };
};

/**
   From http://www.ietf.org/rfc/rfc4287.txt
   The "atom:feed" element is the document (i.e., top-level) element of
   an Atom Feed Document, acting as a container for metadata and data
   associated with the feed.  Its element children consist of metadata
   elements followed by zero or more atom:entry child elements.

   atomFeed =
      element atom:feed {
         atomCommonAttributes,
         (atomAuthor*
          & atomCategory*
          & atomContributor*
          & atomGenerator?
          & atomIcon?
          & atomId
          & atomLink*
          & atomLogo?
          & atomRights?
          & atomSubtitle?
          & atomTitle
          & atomUpdated
          & extensionElement*),
         atomEntry*
      }
*/
class AtomFeedBase
{
public:
    QString id;
    QString title;
    QList<Author> authors;
    QList<Category> categories;
    QList<Link> links;
    QDateTime published;
    QDateTime updated;
    Generator generator;

    virtual void clear() = 0;
};

class AtomFeed : public AtomFeedBase
{
public:
    QList<AtomEntry*> entries;

    virtual void clear() {
        this->id.clear();
        this->title.clear();
        this->authors.clear();
        this->categories.clear();
        this->links.clear();
        for(int i=0;i<this->entries.size();i++)
            if(entries.at(i) != NULL) delete entries.at(i);
        this->published = QDateTime();
    }
};
#endif // QTGDATAATOMFEED_H
