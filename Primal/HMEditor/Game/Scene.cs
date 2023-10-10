using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace HMEditor.Game
{
    [DataContract]
    class Scene : ViewModelBase
    {
        private string mName;
        [DataMember]
        public string Name
        {
            get => mName;
            set
            {
                mName = value;
                OnPropertyChanged(nameof(Name));
            }
        }

        [DataMember]
        public Project Project { get; private set; }

        private bool mbIsActive;
        [DataMember]
        public bool IsActive
        {
            get => mbIsActive;
            set
            {
                mbIsActive = value;
                OnPropertyChanged(nameof(IsActive));
            }
        }

        public Scene(Project project, string name)
        {
            Debug.Assert(project != null);
            Project = project;
            Name = name;
        }
    }
}
