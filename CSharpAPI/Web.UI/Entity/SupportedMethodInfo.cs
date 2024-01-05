namespace Web.UI.Entity;

public class SupportedMethodInfo
{
    public Dictionary<string, Dictionary<string, List<string>>> OneStepMethodInfo { get; set; }
    public Dictionary<string, Dictionary<string, List<string>>> MultiStepMethodInfo { get; set; }
}