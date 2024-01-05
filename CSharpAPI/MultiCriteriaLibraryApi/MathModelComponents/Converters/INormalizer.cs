namespace MultiCriteriaLibraryApi.MathModelComponents.Converters;

public interface INormalizer
{
    internal IntPtr getPtr();
    MathModel GetNormalizedMathModel(MathModel mathModel);
}