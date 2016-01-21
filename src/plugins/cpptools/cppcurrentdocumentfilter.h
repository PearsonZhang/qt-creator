/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#ifndef CPPCURRENTDOCUMENTFILTER_H
#define CPPCURRENTDOCUMENTFILTER_H

#include "searchsymbols.h"

#include <coreplugin/locator/ilocatorfilter.h>

namespace Core { class IEditor; }

namespace CppTools {

class CppModelManager;

namespace Internal {

class CppCurrentDocumentFilter : public  Core::ILocatorFilter
{
    Q_OBJECT

public:
    explicit CppCurrentDocumentFilter(CppModelManager *manager,
                                      StringTable &stringTable);
    ~CppCurrentDocumentFilter() {}

    QList<Core::LocatorFilterEntry> matchesFor(QFutureInterface<Core::LocatorFilterEntry> &future, const QString &entry);
    void accept(Core::LocatorFilterEntry selection) const;
    void refresh(QFutureInterface<void> &future);

private slots:
    void onDocumentUpdated(CPlusPlus::Document::Ptr doc);
    void onCurrentEditorChanged(Core::IEditor *currentEditor);
    void onEditorAboutToClose(Core::IEditor *currentEditor);

private:
    QList<IndexItem::Ptr> itemsOfCurrentDocument();

    CppModelManager * m_modelManager;
    SearchSymbols search;

    mutable QMutex m_mutex;
    QString m_currentFileName;
    QList<IndexItem::Ptr> m_itemsOfCurrentDoc;
};

} // namespace Internal
} // namespace CppTools

#endif // CPPCURRENTDOCUMENTFILTER_H