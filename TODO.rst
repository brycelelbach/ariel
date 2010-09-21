Todo
====

 * Write an InstantiationContext class for TemplateSpecializationType
   for obtaining information from a TemplateSpecializationType. Modify
   TIConsumer to store these instead of TemplateSpecializationTypes.
   For now, this class only needs to retrieve the names of an instan-
   -tiation's template arguments as strings.
 * Write a TIWriter class that will generate an XML document from a
   TIConsumer's IR table.
 * Implement proper handling for template functions in TIConsumer.
 * Write a functionality test suite for the profiler. Bugger people into
   providing simple test cases.
 * Write a QT application with python that will parse and display the
   XML output of the profiler. The first stage is using Python's XML
   libraries (specifically, I think ElementTree is well suited for the
   task) to read the XML into an IR of the profile. Then, pretty graphs.
 * Reflect enough of clang -cc1 to Python to make the above QT application
   into a standalone profiler.
