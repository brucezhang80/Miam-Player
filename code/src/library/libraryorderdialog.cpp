#include "libraryorderdialog.h"

#include "library/librarymodel.h"

#include <QtDebug>

LibraryOrderDialog::LibraryOrderDialog(QWidget *parent) :
	QDialog(parent, Qt::Popup)
{
	setupUi(this);

	// Artists \ Albums \ Tracks
	QStandardItemModel *artistModel = new QStandardItemModel(this);
	artistModel->setHorizontalHeaderItem(0, new QStandardItem("Artists \\ Albums"));
	QStandardItem *artist = new QStandardItem("Artist");
	artistModel->appendRow(artist);
	for (int i = 1; i <= 1; i++) {
		QStandardItem *album = new QStandardItem("Album");
		artist->appendRow(album);
		for (int j = 1; j <= 2; j++) {
			album->appendRow(new QStandardItem("0" + QString::number(j) + ". track #" + QString::number(j)));
		}
	}
	artistTreeView->setModel(artistModel);
	artistTreeView->header()->setStyleSheet("QHeaderView::section {	border: 1px solid #66A7E8; background-color: #D1E8FF; }");

	bool disabled = false;

	// Albums \ Tracks
	QStandardItemModel *albumModel = new QStandardItemModel(this);
	albumModel->setHorizontalHeaderItem(0, new QStandardItem("Albums"));
	QStandardItem *album = new QStandardItem("Album");
	albumModel->appendRow(album);
	for (int i = 1; i <= 2; i++) {
		album->appendRow(new QStandardItem("0" + QString::number(i) + ". track #" + QString::number(i)));
	}
	albumTreeView->setModel(albumModel);
	albumTreeView->setDisabled(disabled);

	// Artists - Albums \ Tracks
	QStandardItemModel *artistAlbumModel = new QStandardItemModel(this);
	artistAlbumModel->setHorizontalHeaderItem(0, new QStandardItem("Artists - Albums"));
	QStandardItem *artistAlbum_1 = new QStandardItem("Artist - Album");
	artistAlbumModel->appendRow(artistAlbum_1);
	for (int i = 1; i <= 2; i++) {
		artistAlbum_1->appendRow(new QStandardItem("0" + QString::number(i) + ". track #" + QString::number(i)));
	}
	artistAlbumTreeView->setModel(artistAlbumModel);
	artistAlbumTreeView->setDisabled(disabled);

	// Year \ Artist - Album \ Tracks
	QStandardItemModel *yearModel = new QStandardItemModel(this);
	yearModel->setHorizontalHeaderItem(0, new QStandardItem("Years"));
	QStandardItem *year = new QStandardItem("2013");
	yearModel->appendRow(year);
	QStandardItem *artistAlbum_2 = new QStandardItem("Artist - Album");
	year->appendRow(artistAlbum_2);
	for (int j = 1; j <= 2; j++) {
		artistAlbum_2->appendRow(new QStandardItem("0" + QString::number(j) + ". track #" + QString::number(j)));
	}
	yearTreeView->setModel(yearModel);
	yearTreeView->setDisabled(disabled);

	foreach (QTreeView *treeView, findChildren<QTreeView*>()) {
		treeView->expandAll();
		connect(treeView, &QTreeView::clicked, [=]() {
			foreach (QTreeView *treeView_2, findChildren<QTreeView*>()) {
				if (treeView == treeView_2) {
					treeView_2->header()->setStyleSheet("QHeaderView::section {	border: 1px solid #66A7E8; background-color: #D1E8FF; }");
				} else {
					treeView_2->header()->setStyleSheet("");
				}
			}
			this->close();
		});
	}
}

void LibraryOrderDialog::show()
{
	if (!_model->artists().isEmpty()) {
		qDebug() << "pick one to populate this popup!";
		///FIXME: the list is empty when reading from a file!
		///The model class should really be redesigned completely
	}
	QDialog::show();
}