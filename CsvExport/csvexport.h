#ifndef CSVEXPORT_H
#define CSVEXPORT_H

#include "csvexport_global.h"
#include "plugins/genericexportplugin.h"
#include "config_builder.h"
#include "csvformat.h"

CFG_CATEGORIES(CsvExportConfig,
     CFG_CATEGORY(CsvExport,
         CFG_ENTRY(bool,    ColumnsInFirstRow, false)
         CFG_ENTRY(int,     Separator,         0)
         CFG_ENTRY(QString, CustomSeparator,   QString())
         CFG_ENTRY(QString, NullValueString,   QString())
     )
)

class CSVEXPORTSHARED_EXPORT CsvExport : public GenericExportPlugin
{
        Q_OBJECT

        SQLITESTUDIO_PLUGIN
        SQLITESTUDIO_PLUGIN_TITLE("CSV exporting format")
        SQLITESTUDIO_PLUGIN_DESC("Provides CSV format for exporting")
        SQLITESTUDIO_PLUGIN_VERSION(10000)
        SQLITESTUDIO_PLUGIN_AUTHOR("sqlitestudio.pl")

    public:
        CsvExport();

        QString getFormatName() const;
        ExportManager::StandardConfigFlags standardOptionsToEnable() const;
        ExportManager::ExportModes getSupportedModes() const;
        QString getExportConfigFormName() const;
        CfgMain* getConfig();
        void validateOptions();
        QString defaultFileExtension() const;
        bool beforeExportQueryResults(const QString& query, QList<QueryExecutor::ResultColumnPtr>& columns);
        bool exportQueryResultsRow(SqlResultsRowPtr row);
        bool afterExportQueryResults();
        bool exportTable(const QString& database, const QString& table, const QStringList& columnNames, const QString& ddl, SqliteCreateTablePtr createTable,
                         bool databaseExport);
        bool exportVirtualTable(const QString& database, const QString& table, const QStringList& columnNames, const QString& ddl, SqliteCreateVirtualTablePtr createTable,
                                bool databaseExport);
        bool exportTableRow(SqlResultsRowPtr data);
        bool beforeExportDatabase(const QString& database);
        bool exportIndex(const QString& database, const QString& name, const QString& ddl, SqliteCreateIndexPtr createIndex);
        bool exportTrigger(const QString& database, const QString& name, const QString& ddl, SqliteCreateTriggerPtr createTrigger);
        bool exportView(const QString& database, const QString& name, const QString& ddl, SqliteCreateViewPtr createView);

    private:
        bool exportTable(const QStringList& columnNames, bool databaseExport);
        void defineCsvFormat();

        CFG_LOCAL(CsvExportConfig, cfg)
        CsvFormat format;
};

#endif // CSVEXPORT_H
