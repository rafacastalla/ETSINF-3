﻿//------------------------------------------------------------------------------
// <auto-generated>
//     Este código se generó mediante una herramienta.
//     Los cambios del archivo se perderán si se regenera el código.
// </auto-generated>
//------------------------------------------------------------------------------
namespace ISWVehicleRentalExampleLib.Entities
{
	using System;
	using System.Collections.Generic;
	using System.Linq;
	using System.Text;

	public partial class Category
	{
       
        public string name
        {
            get;
            set;
        }
        public double priceUnlimitedMileage
		{
			get;
			set;
		}

		public double priceFixedMileage
		{
			get;
			set;
		}

		public double priceAdditionalKm
		{
			get;
			set;
		}

		public double priceFullInsurance
		{
			get;
			set;
		}

		public double pricePartialInsurance
		{
			get;
			set;
		}

		public int Id
		{
			get;
			set;
		}

		public virtual Category Upper
		{
			get;
			set;
		}

	}
}

