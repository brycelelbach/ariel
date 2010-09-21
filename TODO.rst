Todo
====

 * Write an InstantiationContext class for TemplateSpecializationType
   for obtaining information from a TemplateSpecializationType. Modify
   TIConsumer to store these instead of TemplateSpecializationTypes.
   For now, this class only needs to retrieve the names of an instan-
   -tiation's template arguments as strings.
 * Write a TIWriter class that will generate a output from a TIConsumer's
   IR table. TIWriter should be an abstract class, classes derived from
   TIWriter should implement a specific output format.
 * Implement proper handling for template functions in TIConsumer.
 * Write a functionality test suite for the profiler. Bugger people into
   providing simple test cases.
