#pragma warning(disable: 4005)
#include "vesp/graphics/Mesh.hpp"
#include "vesp/graphics/Engine.hpp"
#include "vesp/graphics/Camera.hpp"

namespace vesp { namespace graphics {

	Mesh::Mesh()
	{
		this->scale_ = Vec3(1, 1, 1);
	}

	bool Mesh::Create(ArrayView<Vertex> vertices, D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		if (!this->vertexBuffer_.Create(vertices))
			return false;

		PerMeshConstants constants;

		if (!this->perMeshConstantBuffer_.Create(constants))
			return false;

		this->topology_ = topology;

		return true;
	}

	Vec3 Mesh::GetPosition()
	{
		return this->position_;
	}

	void Mesh::SetPosition(Vec3 const& position)
	{
		this->SetPositionAngle(position, this->GetAngle());
	}

	Quat Mesh::GetAngle()
	{
		return this->angle_;
	}

	void Mesh::SetAngle(Quat const& angle)
	{
		this->SetPositionAngle(this->GetPosition(), angle);
	}

	void Mesh::SetPositionAngle(Vec3 const& position, Quat const& angle)
	{
		this->position_ = position;
		this->angle_ = angle;
	}

	Vec3 Mesh::GetScale()
	{
		return this->scale_;
	}

	void Mesh::SetScale(Vec3 const& scale)
	{
		this->scale_ = scale;
	}

	void Mesh::SetScale(F32 scale)
	{
		this->SetScale(Vec3(scale, scale, scale));
	}

	void Mesh::SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
	{
		this->topology_ = topology;
	}

	D3D11_PRIMITIVE_TOPOLOGY Mesh::GetTopology()
	{
		return this->topology_;
	}

	void Mesh::Draw()
	{
		this->UpdateMatrix();
		this->vertexBuffer_.Use(0);
		this->perMeshConstantBuffer_.UseVS(1);
		Engine::ImmediateContext->IASetPrimitiveTopology(this->topology_);
		Engine::ImmediateContext->Draw(this->vertexBuffer_.GetCount(), 0);
	}

	void Mesh::UpdateMatrix()
	{
		this->world_ = math::Transform(this->position_, this->angle_, this->scale_);

		PerMeshConstants constants;
		constants.world = this->world_;
		constants.worldView = 
			this->world_ * Engine::Get()->GetCamera()->GetView();
		constants.worldViewInverseTranspose = 
			glm::transpose(glm::inverse(constants.worldView));

		this->perMeshConstantBuffer_.Load(constants);
	}

} }