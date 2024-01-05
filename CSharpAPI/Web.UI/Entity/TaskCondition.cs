namespace Web.UI.Entity;

using Web.UI.Entity.Inner;

public class TaskCondition
{
    public Criteria[] CriteriaList { get; set; }
    public Alternative[] AlternativeList { get; set; }
    public CriteriaRelation CriteriaRelation { get; set; }
    public MethodInfo MethodInfo { get; set; }

    public TaskCondition()
    {
        CriteriaList = Array.Empty<Criteria>();
        AlternativeList = Array.Empty<Alternative>();
    }
}