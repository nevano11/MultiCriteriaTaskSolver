namespace Web.UI.Entity;

public class ReferenceInfo<T>
{
    public string Name { get; set; }
    public Dictionary<string, Type> Values { get; set; }
}